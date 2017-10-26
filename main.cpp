
//tutorial URL : https://www.youtube.com/watch?v=OAv2QsOZ4l4&t=264s
//gcc main.cpp -o play.out -lncurses ||| this command compiles this file.
//./play.out ||| this command executes the compiled file.

#include <cstdlib>
#include <ncurses.h>

bool gameOver;
const int width = 20, height = 20;
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

  getch();  //when a key is pressed this translates that pressed key into a readable int.
  endwin(); //this has to be called after ending curses mode
  refresh();  //this gets the building process going

}

void Input() {

  keypad(stdscr, TRUE); //this prepares the computer to take in inputs.
  halfdelay(1); //this makes it so the snake keeps moving the direction you give it.

  int c = getch(); //this save the ACII code of the key that was pressed to c.

    if (c != ERR) {

      //this handles what happens when specific btns are pressed.
      switch(c) {
        case KEY_LEFT:
          dir = LEFT;
          break;
        case KEY_RIGHT:
          dir = RIGHT;
          break;
        case KEY_UP:
          dir = UP;
          break;
        case KEY_DOWN:
          dir = DOWN;
          break;
        case 113: //113 is the ACII code for q.
          gameOver = true;
          break;
      }
    }

}

void Logic() {

//this makes the snake move
  switch(dir) {
    case LEFT:
      x--;
      break;
    case RIGHT:
      x++;
      break;
    case UP:
      y--;
      break;
    case DOWN:
      y++;
      break;
    default :
      break;
  }

  if(x > width || x < 1 || y > height || y < 1) {
    gameOver = true;
  }
  if(x == fruitX && y == fruitY) {
    score++;
    fruitX = (rand() % width) + 1;  //this respawns food.
    fruitY = (rand() % height) + 1;
  }

}

int main() {

  Setup();

  while(!gameOver) {
    Draw();
    Input();
    Logic();
  }

  getch();
  endwin();
  return 0;
}
