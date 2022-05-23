# Brave_Solider
_Trịnh Đức Thành - 21020792_
 
Project này mình làm về game Brave Solider phỏng theo game [Contra](https://gamevui.vn/contra/game) sử dụng thư viện đồ họa [SDL2](https://www.libsdl.org/) và ngôn ngữ [C++](https://vi.wikipedia.org/wiki/C%2B%2B).

### Hướng dẫn cài đặt:
- Bước 1: Tải source code vào máy của bạn bằng cách nhấn vào `Code` chọn `Dowload Zip`.
- Giải nén file zip vừa mới tải sau đó vào đường dẫn BraveSolider/Lession2.exe để chạy trò chơi.

### 2. Mô tả chung:
- Điều khiển nhân vật đi đến cuối map bản đồ.
- Di chuyển khéo léo để tránh đạn, đồng thời hạ gục quái vật để ghi điểm.
- Nhặt đồng xu cũng giúp tăng thêm điểm
- Linh hoạt thay đổi hướng đạn để bắn dễ dàng hơn
 
### 3. Các chức năng:
> Video minh họa: 
> [BraveSolider](https://www.youtube.com/watch?v=GpWHwqQ7T-M)
- Điểm cao nhất
- Hiển thị thời gian, số mạng, điểm
- Di chuyển map bản đồ, nhảy, rơi xuống vực thẳm...
- Có các ThreatObject di chuyển cũng như có đạn bắn.
- Có đối tượng phụ trợ là đồng tiền để tăng điểm.

 
### 4. Các kĩ thuật sử dụng:
- Thư viện đồ họa SDL2: Sử dụng hiển thị ảnh, chữ, phát âm thanh...
- Kĩ thuật di chuyển map bản đồ theo nhân vật.
- Mảng 2 chiều: dùng xây dựng map bản đồ.
- Fps: Đặt fps cố định là 28 khung hình trên giây để cho nhân vật di chuyển một cách ổn định, dễ nhìn.
- Kĩ thuật tile map để xay dựng bản đồ.
- Đọc, in dữ liệu ra file: dùng để lưu trữ dữ liệu thành tích, tránh bị mất mỗi lần chạy game.
- Cấu trúc, lớp..
- Kĩ thuật lập trình hướng đối tượng.
- Xử lí va chạm.
- Chia code thành các file.
- Có thể chơi lại nhiều lần
- Photoshop: Cắt ghép ảnh, tách nhân vật từ ảnh game gốc cũng như chỉnh sửa các ảnh trên mạng theo ý thích để đưa vào game.

### 5. Kết luận:
Sau khi hoàn thành dự án game cuối kì này, em học được rất nhiều kiến thức và kinh nghiệm, từ tư duy code, kĩ năng chỉnh sửa ảnh cho đến việc lên ý tưởng, quản lý thời gian.
 
**- Điều tâm đắc:**
 
Phát triển thành công logic về xảy ra va chạm cũng như tự xây dựng được menu trò chơi, chức năng replay.
 
**- Các hướng phát triển trong tương lai:**
 
- Nâng cao hơn kỹ năng photoshop để có đồ họa đẹp hơn cho game.
- Xây dựng menu đẹp hơn, thêm các chức năng pause/resume game.
- Xây dựng thêm Boss Object có hiển thị thanh máu bên trên.
- Xử lí thêm các hướng đạn bắn và thêm các item phụ trợ cũng như đa dạng hơn.
- Xử lí AI quái tự chạy về phía người khi lại gần.
