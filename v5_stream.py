import serial, glob, os

ports = glob.glob("/dev/ttyACM*")
if not ports:
    print("❌ No controller found on /dev/ttyACM*")
    exit(1)

port = ports[0]
print(f"🔗 Connected to controller on {port}")

# Compile the latest changes
os.system("make quick")

if not os.path.exists("bin/hot.package.bin"):
    print("❌ Compiled binary not found!")
    exit(1)

# V5 Header packet to force the brain to write to Slot 1
# This tells the V5 Brain exactly where to save the incoming bytes
header = b"\x1b\x21\x01\x00"  # V5 Sync + Slot 1 Write Command

with serial.Serial(port, 115200, timeout=2) as s:
    print("📥 Sending program initialization header...")
    s.write(header)
    
    print("🚀 Streaming binary data to Slot 1...")
    with open("bin/hot.package.bin", "rb") as f:
        s.write(f.read())
        
    print("✅ Upload Complete! Check your V5 Brain screen.")
