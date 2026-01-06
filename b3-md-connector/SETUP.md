# B3 Market Data Connector - Production Setup Guide

This guide walks you through configuring and running the B3 MD connector in production.

## Prerequisites

Before you start, you need to obtain from B3:

1. **Multicast Connectivity Information**:
   - Multicast IPs and ports for your channel(s)
   - Three feeds per channel: Instrument, Incremental, Snapshot
   - Test environment and Production environment addresses

2. **OnixS License**:
   - Purchase from OnixS Solutions
   - License files for B3 UMDF Market Data Handler

3. **Network Access**:
   - Network interface(s) configured to receive multicast traffic
   - Firewall rules allowing multicast UDP packets
   - IGMP configured on your switches/routers

## Step 1: OnixS License Setup

1. Place your OnixS license files in a directory:
   ```bash
   mkdir -p /opt/onixs/licenses
   cp OnixS.License.B3.UMDF.* /opt/onixs/licenses/
   ```

2. Verify the license is readable:
   ```bash
   ls -la /opt/onixs/licenses/
   ```

## Step 2: B3 Connectivity Configuration

1. Create the connectivity XML file with the multicast addresses provided by B3:

   ```bash
   cd /home/damian/repos/B3-Connector/b3-md-connector
   cp b3-connectivity.xml.example b3-connectivity.xml
   ```

2. Edit `b3-connectivity.xml` and replace the placeholder IPs:

   ```xml
   <configuration environment="PROD">
     <channel id="80">
       <!-- Replace XXX with actual B3 multicast IPs -->
       <instrument>
         <a ip="233.XXX.XXX.XXX" port="33080"/>
       </instrument>
       <snapshot>
         <a ip="233.XXX.XXX.XXX" port="34080"/>
       </snapshot>
       <incremental>
         <a ip="233.XXX.XXX.XXX" port="31080"/>  <!-- Feed A -->
         <b ip="233.XXX.XXX.XXX" port="31080"/>  <!-- Feed B -->
       </incremental>
     </channel>
   </configuration>
   ```

3. **Important**: Use the addresses provided by B3 for your environment (Test or Prod).

## Step 3: Connector Configuration

1. Create the connector configuration file:

   ```bash
   cp b3-md-connector.conf.example b3-md-connector.conf
   ```

2. Edit `b3-md-connector.conf`:

   ```ini
   # OnixS Configuration
   onixs.license_dir=/opt/onixs/licenses
   onixs.connectivity_file=/home/damian/repos/B3-Connector/b3-md-connector/b3-connectivity.xml
   onixs.channel=80

   # Network Interfaces (Linux only, find with: ip addr)
   onixs.if_a=eth0
   onixs.if_b=eth1

   # Pipeline Configuration
   md.shards=8  # Increase for high throughput

   # Client Endpoints
   sub.endpoint=tcp://*:8080
   pub.endpoint=tcp://*:8081
   ```

3. **Network Interface Selection**:
   - Find your interface names: `ip addr` or `ifconfig`
   - Use the interface connected to the network segment receiving B3 multicast
   - If unsure, leave empty for automatic selection

## Step 4: Network Verification

Before running the connector, verify multicast connectivity:

1. **Check multicast routing**:
   ```bash
   route -n | grep 224
   ```

2. **Test multicast reception** (requires B3 to be actively sending):
   ```bash
   # Listen on B3 incremental feed (example)
   sudo tcpdump -i eth0 -n host 233.XXX.XXX.XXX and port 31080
   ```

3. **Verify IGMP membership** (after connector starts):
   ```bash
   netstat -g
   ```

## Step 5: Build and Run

**Inside the b3-md-connector devcontainer:**

```bash
# Build
cd /workspaces/MarketHub.B3Connector
cmake --build build/md --target b3-md-connector

# Run
./build/md/b3-md-connector b3-md-connector/b3-md-connector.conf
```

## Expected Startup Sequence

```
[startup] cwd=/workspaces/MarketHub.B3Connector
[startup] config=b3-md-connector/b3-md-connector.conf
[startup] onixs.license_dir=/opt/onixs/licenses
[startup] onixs.connectivity_file=.../b3-connectivity.xml
[startup] onixs.channel=80
[startup] onixs.if_a=eth0
[startup] onixs.if_b=eth1
[startup] md.shards=8
[startup] starting OnixS handler...

# OnixS connects to multicast feeds...
# SecurityDefinitions arrive from instrumentFeed
# InstrumentRegistry gets populated

[startup] starting subscription server...
[runtime] running. Press ENTER to stop...

# Every 5 seconds, health metrics:
[2026-01-06 10:00:00] [info] [worker] code=health_tick shard=0 qsize=0 enq=150 pub=150
[2026-01-06 10:00:00] [info] [publishing] code=health_tick arg0=0 arg1=12000
```

## Step 6: Verify Operation

### Check Registry Population

Look for log messages indicating SecurityDefinitions were received. The registry should populate within the first few seconds.

### Test Client Connection

From another terminal:

```bash
# Simple netcat test to subscription server
echo "test" | nc localhost 8080

# Or use the test client (if built)
./build/md/test-client PETR4
```

### Monitor Health Metrics

Health ticks every 5 seconds show:
- **qsize=0**: No backpressure (queue empty)
- **enq=X pub=X**: Messages received and published (should be equal)
- **arg0=0**: No drops

If you see sustained drops or high qsize, increase `md.shards`.

## Troubleshooting

### Problem: OnixS fails to start with license error

**Solution**:
- Verify license file exists: `ls /opt/onixs/licenses/`
- Check file permissions are readable
- Confirm license is valid for B3 UMDF (not BOE)

### Problem: No SecurityDefinitions received

**Possible causes**:
1. **Multicast not reaching server**:
   - Check firewall rules
   - Verify IGMP is configured on switches
   - Use `tcpdump` to verify packets are arriving

2. **Wrong channel configured**:
   - Verify `onixs.channel` matches the channel in connectivity file
   - Check B3 documentation for correct channel ID

3. **Connectivity file incorrect**:
   - Verify XML syntax is valid
   - Confirm IPs match B3 specification document

### Problem: No OrderBook updates received

**Check**:
1. Registry must be populated first (SecurityDefinitions received)
2. Client must send `MarketDataSuscriptionRequest` to port 8080
3. OnixS calls `handler.subscribe(instrumentId)` for that instrument
4. B3 must be actively sending data for that instrument during trading hours

### Problem: High drops in health metrics

**Solutions**:
- Increase `md.shards` (more parallel workers)
- Check CPU usage (`top` or `htop`)
- Verify network isn't saturated

## B3 Channels Reference

Common B3 UMDF channels:

| Channel | Asset Class | Examples |
|---------|-------------|----------|
| 80 | Equities (Bovespa) | PETR4, VALE3, ITUB4 |
| 82 | Options | PETR4C45, VALE3P40 |
| 84 | Futures | WINZ23, DOLZ23 |
| 86 | BM&F Agricultural | SOYB, CORN |
| 88 | BM&F Financial | DI1, DAP |
| 90-98 | Other asset classes | Various |

## Production Checklist

- [ ] OnixS license installed and readable
- [ ] Connectivity XML file with real B3 IPs (not example IPs)
- [ ] Network interfaces configured for multicast
- [ ] Firewall rules allow multicast UDP
- [ ] IGMP configured on network switches
- [ ] Config file edited with production values
- [ ] Tested in B3 Test environment first
- [ ] Monitoring/alerting configured for health metrics
- [ ] Documented rollback procedure

## Support

- **OnixS SDK Issues**: support@onixs.biz
- **B3 Connectivity Issues**: Contact B3 support
- **Connector Issues**: Check GitHub issues or logs
