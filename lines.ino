#include <Arduino.h>
#include <U8g2lib.h>

U8G2_ST7920_128X64_F_SW_SPI u8g2(U8G2_R0, /* clock=*/ 13, /* data=*/ 11, /* CS=*/ 10, /* reset=*/ 8);

void setup(void) {
    Serial.begin(9600);
    u8g2.begin();
}

void loop(void) {

    u8g2.clearBuffer();
    
    //draw
    draw();

    u8g2.sendBuffer();

    delay(500);
}

void my_line(float x1, float y1, float x2, float y2) {

    // y = mx + c
    float slope = (y1-y2) / (x1-x2);
    float c = y1 - (slope * x1);

    // check for near-vertical line
    // if vertical, y = x1.
    // else, draw as y = mx + c

    // if vertical
    if (x1 == x2) {

        int startY;
        int endY;

        // calculate which y coord is smaller
        if (y1 < y2) {
            startY = y1;
            endY = y2;
        }
        else {
            startY = y2;
            startY = y1;
        }
    
        // draw pixels
        for (int y = startY; y <= endY; y++) {
            
            u8g2.drawPixel(x1, y);
        }
    }

    // if not
    else {
        
        // calculate which x coord is smaller
        int startX;
        int endX;
        if (x1 < x2) {
            startX = x1;
            endX = x2;
        }
        else {
            startX = x2;
            endX = x1;
        }

        // draw pixels
        for (int x = startX; x < endX; x++)  {
            int y = (slope*x) + c;
            u8g2.drawPixel(x, y);
        }
    }

    /*
    u8g2.setFont(u8g2_font_ncenR08_tr);
    u8g2.setCursor(0, 8);
    u8g2.print("m = ");
    u8g2.print(slope);
    u8g2.print(",    c = ");
    u8g2.print(c);
    */
}

void my_box(float x, float y, float w, float h) {
    
    float hW = w/2;
    float hH = h/2;

    // top
    my_line(x-hW, y-hH, x+hW, y-hH);

    // right
    my_line(x+hW, y-hH, x+hW, y+hH);

    // bottom
    my_line(x-hW, y+hH, x+hW, y+hH);

    // left
    my_line(x-hW, y-hH, x-hW, y+hH);
}

int my_dist(int x1, int y1, int x2, int y2) {
    return( sqrt((x1-x2)*(x1-x2) + (y1-y2)*(y1-y2)) );
}

void my_circle(int x, int y, int r) {
    for (int i = x-r; i < x+r; i++) {
        for (int j = y-r; j < y+r; j++) {
            if (my_dist(x, y, i, j) < r) {
                u8g2.drawPixel(i, j); 
            }
        }
    }
}

void my_hollowCircle(int x, int y, int r) {
    for (int i = x-r; i < x+r+1; i++) {
        for (int j = y-r; j < y+r+1; j++) {
            if (my_dist(x, y, i, j) > r-1 && my_dist(x, y, i, j) < r+1) {
                u8g2.drawPixel(i, j); 
            }
        }
    } 
}


int r = 0;

void draw() {

}
