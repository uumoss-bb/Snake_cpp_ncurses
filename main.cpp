
//gcc main.cpp -o play.out -lncurses ||| this command compiles this file.
//./play.out ||| this command executes the compiled file.

#include <cstdlib>
#include <ncurses.h>

bool gameOver;
const int width = 40, height = 20;
int x, y, fruitX, fruitY, score;  //this is the position of the head of the snake, and its food.
enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};  //this is an enumeral. The direction the snake is going.
eDirection dir;

void Setup() {

  initscr();  //basicaly starts the screen up, and displays error messages if there is one.
  clear();  //this clears everything but the screen.
  noecho(); //makes it so characters typed are not echoed?
  cbreak(); //This makes it so the computer takes in data one character at a time. Its inbetween raw and cooked mode.
  curs_set(0);  //this hides the curser.

  gameOver = false;
  dir = STOP;
  x = width / 2;  //this sets the inicial position of the head.
  y = height / 2;
  fruitX = (rand() % width) + 1;  //this sets position of the food.
  fruitY = (rand() % height) + 1;
  score = 0;

}

void Draw() {

  clear();

  //building process
  for (int i = 0; i < height + 2; i++) {

    for (int j = 0; j < width + 2; j++) {

      if(i == 0 | i == height + 1) {  //this builds the top and bottom boundaries.
        mvprintw(i, j, "+");
      }
      else if(j == 0 | j == width + 1) {  //this builds the left and right boundaries.
        mvprintw(i, j, "+");
      }
      else if(i == y && j == x) {  //this builds the snake head.
        mvprintw(i, j, "o");
      }
      else if (i == fruitY && j == fruitX) { //this builds the snake food.
        mvprintw(i, j, "@");
      }

    }
  }

  mvprintw(23, 33, "Score %d", score);  //this displays the score.

  refresh();  //this gets the building process going

  getch();  //when a key is pressed this translates that pressed key into a readable int.
  endwin();

}

void Input() {

}

void Logic() {

}

int main() {

  Setup();

  while(!gameOver) {

    Draw();
    Input();
    Logic();
  }

  return 0;
}
