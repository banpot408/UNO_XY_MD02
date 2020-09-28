# UNO_XY_MD02
XY-MD02 Manual : http://www.sah.co.rs/media/sah/techdocs/xy-md02-manual.pdf

Wiring Diagram

![Wiring diagram](https://user-images.githubusercontent.com/30364896/78583121-95953a80-7860-11ea-82fc-86893150ae25.jpg)

 1. Download Library from this link https://www.arduinolibraries.info/libraries/modbus-master

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


การแก้ไข Address 
1. เราสามารถใช้ function code 03 read id ของ sensor ได้แบบนี้ครับ ต้องอ่านที่ address 0x101 ฐาน 16 แต่ถ้าเป็น ฐาน 10 จะเป็น 257 ดังรูป ครับ
![120196784_3949073175107068_820209319172435833_n](https://user-images.githubusercontent.com/30364896/94477894-aebde900-01fc-11eb-9e93-2e4978bd40be.jpg)
ในรูปเป็น sensor ใหม่ ยังไม่มีการแก้ไข id จะเป็น 0001 ครับ

2. จากนั้นเปลี่ยนเป็นฟังก์ชั่น 06 แล้วกรอด id ที่ต้องการเปลี่ยนลงไป แล้วกด enter จากนั้นกดปุ่ม read / write 1 ครั้ง ดังรูปครับ
![120342026_3949088715105514_5595343871691343389_n](https://user-images.githubusercontent.com/30364896/94477937-bc736e80-01fc-11eb-82a4-6689e967e8b0.jpg)
จากรูปผมจะแก้เป็น id 0002

3. ลองกลับมาใช้ function code 03 read id ของ sensor จะได้แบบนี้ครับ
![120333449_3949092078438511_1304343671685406198_n](https://user-images.githubusercontent.com/30364896/94477998-d44af280-01fc-11eb-9f34-9e941e8b09f0.jpg)

4. ลองใช้ function code 04 read id ของ sensor จะได้แบบนี้ครับ
![120231940_3949102778437441_5333050690998021976_n](https://user-images.githubusercontent.com/30364896/94478031-df058780-01fc-11eb-8559-b7bbfa6d81fe.jpg)
จะเห็นว่า id ยังคงเป็น 0001 เหมือนเดิม เพราะยังสามารถอ่านได้

5. แนะนำให้ทำการ หยุดจ่ายไฟให้ sensor สัก 1 นาทีแล้ว ลอง read ด้วย id ที่ตั้งค่าไปใหม่อีกครั้ง ถ้าสามารถอ่านได้ แสดงว่าการแก้ id ของเรา สมบูรณ์ แล้วครับ แบบ นี้
![120174983_3949090565105329_1200018905743181327_n](https://user-images.githubusercontent.com/30364896/94477924-b8dfe780-01fc-11eb-9cb1-f68d6511d2e0.jpg)












