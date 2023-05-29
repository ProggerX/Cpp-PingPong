#include<ncurses.h>
#include<unistd.h>
#include<cstdlib>
using namespace std;

const int window_height = 20, window_width = 40;

class Platform
{
	public:
		int x = 0;
		void draw()
		{
			mvwprintw(stdscr, window_height, x, "########");
		}
};

int score = 0;

class Ball
{
	private:
		int x = 0 , y = 0;
		bool isRight = true;
		bool isDown = true;
	public:
		void update(Platform plat)
		{
			clear();
			if(isRight && isDown)
			{
				if(x + 2 > window_width)
				{
					x-=2;
					isRight = false;
				}
				else x+= 2;
				if(y + 1 == window_height)
				{
					if(x >= plat.x && x <= plat.x + 8)
					{
						y--;
						isDown = false;
						score++;
					}
					else y++;
				}
				else if(y + 1 > window_height)
				{
					clear();
					nodelay(stdscr, false);
					mvwprintw(stdscr, window_height / 2, window_width / 2 - 7, "Game over!, score: %d", score);
					getch();
					endwin();
					exit(0);

				}
				else y++;
			}
			if(isRight && !isDown)
			{
				if(x + 2 > window_width)
				{
					x-=2;
					isRight = false;
				}
				else x+=2;
				if(y <= 0)
				{
					isDown = true;
					y++;
				}
				else y--;
			}
			if(!isRight && isDown)
			{
				if(x - 2 < 0)
				{
					x+=2;
					isRight = true;
				}
				else x-=2;
				if(y + 1 == window_height)
				{
					if(x >= plat.x && x <= plat.x + 8)
					{
						y--;
						isDown = false;
						score++;
					}
					else y++;
				}
				else if(y + 1 > window_height)
				{
					clear();
					nodelay(stdscr, false);
					mvwprintw(stdscr, window_height / 2, window_width / 2 - 7, "Game over!, score: %d", score);
					getch();
					endwin();
					exit(0);
				}
				else y++;
			}
			if(!isRight && !isDown)
			{
				if(x - 1 < 0)
				{
					x+=2;
					isRight = true;
				}
				else x-=2;
				if(y <= 0)
				{
					isDown = true;
					y++;
				}
				else y--;
			}
			mvwprintw(stdscr, y, x, "@");
			mvwprintw(stdscr, window_height + 1, 0, "Score: %d", score);
		}
};

int main()
{
	initscr();
	curs_set(0);
	nodelay(stdscr, true);
	Ball ball;
	Platform platform;
	while(true)
	{
		char ch = getch();
		if(ch == 'd' && platform.x + 4 + 8 <= window_width)
		{
			platform.x+=4;
		}
		if(ch == 'a' && platform.x - 4 >= 0)
		{
			platform.x-=4;
		}
		ball.update(platform);
		platform.draw();
		refresh();
		usleep(70000);
	}
	endwin();
}
