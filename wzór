-- functions for accessing Microchip 47L04/47C04/47L16/47C16 I2C Serial EERAM

-- Status Register:
--bit 7 AM: Array Modified bit
--      1 = SRAM array has been modified
--      0 = SRAM array has not been modified
--bit 6-5 Unimplemented: Read as ‘0’
--bit 4-2 BP<2:0>: Block Protect bits
--      000 = Entire array is unprotected
--      001 = Upper 1/64 of array is write-protected
--      010 = Upper 1/32 of array is write-protected
--      011 = Upper 1/16 of array is write-protected
--      100 = Upper 1/8 of array is write-protected
--      101 = Upper 1/4 of array is write-protected
--      110 = Upper 1/2 of array is write-protected
--      111 = Entire array is write-protected
--bit 1 ASE: Auto-Store Enable bit
--      1 = Auto-Store feature is enabled
--      0 = Auto-Store feature is disabled
--bit 0 EVENT: Event Detect bit
--      1 = An event was detected on the HS pin
--      0 = No event was detected on the HS pin

-- read a byte from status register
function readStatus()
   i2c.start(id)
   i2c.address(id,0x18,i2c.RECEIVER)     -- 0x18 is control register
   data=i2c.read(0x00,1)                 -- 0x00 is address of status register
   i2c.stop(id)
   return data
end

-- write a byte to the status register
function writeStatus(data)
   i2c.start(id)
   i2c.address(id,0x18,i2c.TRANSMITTER)   -- 0x18 is control register
   i2c.write(id,0x00)                     -- 0x00 is address of status register
   i2c.write(id,data)
   i2c.stop(id)
end

-- enable the EERAM auto store function
function EnableAutoStore()
   writeStatus(0x82)
end

-- write a byte to the command register. The COMMAND register is a write-only register that allows the 
-- user to execute software-controlled Store and Recall operations.
function writeCommand(data)
   i2c.start(id)
   i2c.address(id,0x18,i2c.TRANSMITTER)   -- 0x18 is control register
   i2c.write(id,0x55)                     -- 0x55 is address of control register
   i2c.write(id,data)
   i2c.stop(id)
end

-- The Software Store command initiates a manual Store operation.
function Store()
   writeCommand(0x33)
end

-- The Software Recall command initiates a manual Recall operation.
function Recall()
   writeCommand(0xDD)
end;

-- write bytes (data) to sequential SRAM locations starting at 'address'.
function writeSRAM(address,data,...)
  local arg={n=select('#',...),...}
  i2c.start(id)
  i2c.address(id,0x50,i2c.TRANSMITTER)          -- 0x50 is SRAM register
  i2c.write(id,address/256,address%256,data)    -- write address high byte, address low byte, first data byte
  for i = 1,arg.n do i2c.write(id,arg[i]) end   -- write sequential data bytes
  i2c.stop(id)  
end

-- read a byte from SRAM location 'address'
function readSRAM(address)
   i2c.start(id)
   i2c.address(id,0x50,i2c.TRANSMITTER)         -- 0x50 is SRAM register
   i2c.write(id,address/256,address%256)        -- address high byte, address low byte
   i2c.stop(id)
   i2c.start(id)
   i2c.address(id,0x50,i2c.RECEIVER)            -- 0x50 is control register
   data=i2c.read(0x00,1)                        -- 0x00 is address of status register
   i2c.stop(id)
   return data
end

-- zero all SRAM locations
function clearSRAM()
   for high=0,0x07 do
      print("page 0x"..string.format("%02X",high))
      tmr.wdclr()
      for low=0,0xFF do
         writeSRAM((high*256)+low,0)
      end
   end
end

-- print the contents of the status register as two hex digits
function printStatus()
   print("0x" .. string.format("%02X",string.byte(readStatus())))
end;

-- print the contents of a SRAM location as two hex digits
function printSRAM(addr)
   print("0x" .. string.format("%02X",string.byte(readSRAM(addr))))
end

-- initialize i2c for the EERAM
sda=6 -- pin 5 on 47C04 connected to GPIO12 of the EPS8266 ESP-12
scl=5 -- pin 6 on 47C04 connected to GPIO14 of the EPS8266 ESP-12
id =0  --always zero
i2c.setup(id,sda,scl,i2c.SLOW)
- See more at: http://www.esp8266.com/viewtopic.php?f=19&t=12427#sthash.oMX6sH8w.dpuf
