// class Spider {
// private:
//     enum State { ALIVE, DEAD } state;
//     RGBApixmap pix[2];
//     float directionX, directionY; // Direction of movement
//     int spiderWidth, spiderHeight;
// public:
//     float pos_X, pos_Y;
//     bool isMoving;
//     float spiderSpeed;
//     Spider() {}

//     Spider(Point2 pos) {
//         isMoving = true;
//         spiderSpeed = 60.0f; // Movement speed
//         this->pos_X = pos.getX();
//         this->pos_Y = pos.getY();
//         directionX = 0.5f; // Initial direction (moving right)
//         directionY = 1.0f; // Initial direction (moving up)
//         spiderWidth = 100; // Set desired width
//         spiderHeight = 100; // Set desired height

//         string fname[2] = { "spider.bmp", "mak3.bmp" }; // Replace with actual image filenames
//         for (int i = 0; i < 2; i++) {
//             pix[i].readBMPFile(fname[i], 1);
//             pix[i].setChromaKey(255, 255, 255);
//         }
//     }