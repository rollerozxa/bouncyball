#include <ncurses.h>
#include <unistd.h>

struct Vec2 {
	int x;
	int y;
};

struct Object {
	Vec2 pos;
	Vec2 vel;
};

Object ball = { {0,0}, {1,1} };

Vec2 res = { 0,0 };
Vec2 res_old = { 0,0 };

#ifdef PDCURSES
// For some god forsaken reason PDCurses does not provide the proper dimensions.
# undef getmaxyx
# define getmaxyx(win,y,x) (y = 25, x = 80)
#endif

int main() {
	initscr();
	noecho();
	timeout(0);
	curs_set(0);

	while (true) {
		getmaxyx(stdscr, res.y, res.x);

		if (res.x != res_old.x || res.y != res_old.y) {
			clear();
		}
		getmaxyx(stdscr, res_old.y, res_old.x);

		if (ball.pos.x == res.x-2)	ball.vel.x = -1;
		if (ball.pos.y == res.y-2)	ball.vel.y = -1;
		if (ball.pos.x == 1)		ball.vel.x = 1;
		if (ball.pos.y == 1)		ball.vel.y = 1;

		for (int x = 0; x < res.x; x++) {
			mvaddch(0, x, ACS_BLOCK);
			mvaddch(res.y-1, x, ACS_BLOCK);
		}

		for (int y = 0; y < res.y; y++) {
			mvaddch(y, 0, ACS_BLOCK);
			mvaddch(y, res.x-1, ACS_BLOCK);
		}

		mvaddstr(ball.pos.y, ball.pos.x, " ");

		ball.pos.x += ball.vel.x;
		ball.pos.y += ball.vel.y;

		mvaddstr(ball.pos.y, ball.pos.x, "O");

		switch (getch()) {
			case 'q':
			case 'Q':
				curs_set(1);
				endwin();
				return 0;
		}

		napms(1000/60);
	}

	endwin();

	return 0;
}
