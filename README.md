# UNO_XY_MD02
XY-MD02 Manual : http://www.sah.co.rs/media/sah/techdocs/xy-md02-manual.pdf

Wiring Diagram

![Wiring diagram](https://user-images.githubusercontent.com/30364896/78583121-95953a80-7860-11ea-82fc-86893150ae25.jpg)

 1. Download Library from this link https://www.arduinolibraries.info/libraries/modbus-master

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


การแก้ไข Address 
1. เราสามารถใช้ function code 03 read id ของ sensor ได้แบบนี้ครับ ต้องอ่านที่ address 0x101 ฐาน 16 แต่ถ้าเป็น ฐาน 10 จะเป็น 257 ดังรูป ครับ

![2020-09-29_2-12-02](https://user-images.githubusercontent.com/30364896/94478498-8edaf500-01fd-11eb-8706-e137eedc503a.png)

ในรูปเป็น sensor ใหม่ ยังไม่มีการแก้ไข id จะเป็น 0001 ครับ

2. จากนั้นเปลี่ยนเป็นฟังก์ชั่น 06 แล้วกรอด id ที่ต้องการเปลี่ยนลงไป แล้วกด enter จากนั้นกดปุ่ม read / write 1 ครั้ง ดังรูปครับ

![2020-09-29_2-16-53](https://user-images.githubusercontent.com/30364896/94478508-926e7c00-01fd-11eb-8b94-b17e6e4d8453.png)

จากรูปผมจะแก้เป็น id 0002

3. ลองกลับมาใช้ function code 03 read id ของ sensor จะได้แบบนี้ครับ

![2020-09-29_2-21-11](https://user-images.githubusercontent.com/30364896/94478524-96020300-01fd-11eb-8ba3-fe19789dcb48.png)

4. ลองใช้ function code 04 read id ของ sensor จะได้แบบนี้ครับ

![2020-09-29_2-21-43](https://user-images.githubusercontent.com/30364896/94478529-97cbc680-01fd-11eb-8702-e2879756394e.png)

จะเห็นว่า id ยังคงเป็น 0001 เหมือนเดิม เพราะยังสามารถอ่านได้

5. แนะนำให้ทำการ หยุดจ่ายไฟให้ sensor สัก 1 นาทีแล้ว ลอง read ด้วย id ที่ตั้งค่าไปใหม่อีกครั้ง ถ้าสามารถอ่านได้ แสดงว่าการแก้ id ของเรา สมบูรณ์ แล้วครับ แบบ นี้

![2020-09-29_2-26-10](https://user-images.githubusercontent.com/30364896/94478539-9ac6b700-01fd-11eb-8231-cbcea9753bd0.png)

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
โปรแกรมที่ใช้โหลดได้จาก   https://sourceforge.net/projects/qmodmaster/
