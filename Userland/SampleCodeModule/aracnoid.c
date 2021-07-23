#include <aracnoid.h>
#include <stdio.h>
#include <callSyscall.h>
#include <timeModule.h>
#include <soundModule.h>
#include <libc.h>
static void update();
static void loadLevel();
static void play();
static void keyHandler(char key);
static void checkBallCollisions();
static int checkRectCollision(Rectangle rec);
static void moveBall();
static void movePlayer();
static void printTime();
static void throwBall();
static void checkWin();

#define SCREEN_WIDTH getScreenWidth()
#define SCREEN_HEIGHT getScreenHeight()

#define DEFAULT_RECT_WIDTH  100
#define DEFAULT_RECT_HEIGHT 15
#define DEFAULT__PLAYER_X_POS  ((SCREEN_WIDTH / 2) - (DEFAULT_RECT_WIDTH) / 2)
#define DEFAULT__PLAYER_Y_POS (SCREEN_HEIGHT - DEFAULT_RECT_HEIGHT) - 10
#define DEFAULT_PLAYER_COLOR 0xF7DE52
#define DEFAULT_PLAYER_X_SPEED 20


#define DEFAULT_BALL_RADIUS 6
#define DEFAULT_BALL_COLOR 0x22CC1A
#define DEFAULT_BALL_X_POS (DEFAULT__PLAYER_X_POS + (DEFAULT_RECT_WIDTH / 2))
#define DEFAULT_BALL_Y_POS (DEFAULT__PLAYER_Y_POS - DEFAULT_BALL_RADIUS - 1)
#define DEFAULT_BALL_X_SPEED 6
#define DEFAULT_BALL_Y_SPEED 6

#define HARD_WALL 0xC93913
#define NORMAL_WALL 0xB0AC9E

#define WALL_ROWS  12
#define WALL_COLUMNS 12
#define DEFAULT_WALL_WIDTH 54
#define DEFAULT_WALL_HEIGHT 20

#define SAVE_KEY 112 //F1
#define RESTART_KEY 'r'

#define BLACK 0x000000
#define WHITE 0xffffff

#define WIN 1
#define LOST 2


typedef struct PlayerStruct{
	Rectangle r;
	int xSpeed;
}Player;

typedef struct BallStruct{
	Circle c;
	int xSpeed;
	int ySpeed;
	int xDir;
	int yDir;
	int thrown;
}Ball;

typedef struct WallStruct{
	Rectangle r;
	int hit;
}Wall;

typedef struct GameStruct{
	Player  player;
	Ball ball;
	Wall  walls[WALL_ROWS][WALL_COLUMNS];
	uint64_t gameTimer;
	uint64_t speedTimer;
	uint64_t score;
}Game;



static Game game ;
static Player player;
static Ball ball;
static int velInc = 1;
static uint64_t savedGame = 0;



static Wall walls[WALL_ROWS][WALL_COLUMNS];

static uint64_t score;
static uint64_t gameTimer;
static uint64_t speedTimer;
static uint64_t gameOver = 0;
static  uint8_t RIGHT,LEFT;
static uint64_t startTime = 0;


void newGame(){
	player.r.x = DEFAULT__PLAYER_X_POS;
	player.r.y = DEFAULT__PLAYER_Y_POS;
	player.r.width =DEFAULT_RECT_WIDTH;
	player.r.height = DEFAULT_RECT_HEIGHT;
	player.r.color = DEFAULT_PLAYER_COLOR;
	player.xSpeed = (int)DEFAULT_PLAYER_X_SPEED;

	ball.c.radius = (int)DEFAULT_BALL_RADIUS;
	ball.c.x = DEFAULT_BALL_X_POS;
	ball.c.y = DEFAULT_BALL_Y_POS;
	ball.c.color = DEFAULT_BALL_COLOR;
	ball.xSpeed = 0;
	ball.ySpeed = 0;
	ball.thrown = 0;

	uint64_t colors[] = {NORMAL_WALL,HARD_WALL};
	int k = 0;
	for(int i = 0; i < 19; i++){
			if(i % 3 != 0){
				for(int j = 0; j < WALL_ROWS;j++){
					Rectangle r = {i*(DEFAULT_WALL_WIDTH),100 + j*(DEFAULT_WALL_HEIGHT + 5),DEFAULT_WALL_HEIGHT,DEFAULT_WALL_WIDTH,colors[(i+j)%2]};
					Wall wall = {r,0};
					 walls[k][j] = wall;
					
				}
				k++;
			}	

	}


	init();

	score = 0;
	gameTimer = 0;
	speedTimer = 0;
	savedGame = 0;
	
	loadLevel();
	drawText("Press Space to throw de ball",340, 5 + 2*CHAR_HEIGHT,WHITE,BLACK);
	play();
}




void save(){
	game.player = player;
	game.ball = ball;
	game.gameTimer = gameTimer;
	game.speedTimer = speedTimer;
	game.score = score;
		for(int i = 0; i < 19; i++){
			for(int j = 0; j < WALL_ROWS;j++){
					game.walls[i][j]= walls[i][j];
				}
		}
		savedGame = 1;
}

void load(){
	
	if(savedGame){
		player = game.player;
		ball = game.ball;
		
		gameTimer = game.gameTimer;
		speedTimer = game.speedTimer;
		score = game.score;
		for(int i = 0; i < 19; i++){
			for(int j = 0; j < WALL_ROWS;j++){
					walls[i][j] = game.walls[i][j];
				}
		}
		loadLevel();
		play();
	}
	

}

uint64_t hasSavedGame(){
	return savedGame;
	
}


static void loadLevel(){
	clearScreen();
	for(int i = 0; i < 19; i++){
		for(int j = 0; j < WALL_ROWS;j++){
			Wall wall = walls[i][j];
			if(!wall.hit){
				drawRect(wall.r.x, wall.r.y, wall.r.width,wall.r.height,wall.r.color);
			}
			
		}
	}
	drawCircle(ball.c.x, ball.c.y, ball.c.radius, ball.c.color);
	drawRect(player.r.x, player.r.y, player.r.width,player.r.height,player.r.color);	
	
}


static void checkWin(){
	if(score == WALL_COLUMNS * WALL_ROWS){
		gameOver = WIN;
	}
}


static void play(){
	
		gameOver = 0;
		
		

		char key;
		while(!gameOver && !((key=getchar()) == SAVE_KEY) && !(key == RESTART_KEY) ){
		
			keyHandler(key);
			update();
			if(ball.thrown && getSeconds()- startTime == 1){
				
				startTime = getSeconds();
				gameTimer++;
				speedTimer++;
				if(speedTimer >= 15){
					beep(1,1000);
					beep(2,1000);
					ball.xSpeed += velInc;
					ball.ySpeed += velInc;
					speedTimer = 0;
				}
			}
			printTime();
			sleep(1);
			
			
		}
		if(gameOver){

			if(gameOver == WIN){
						drawText("YOU WON!", 480,5 + CHAR_HEIGHT,WHITE,BLACK);
						beep(1,1000);
						beep(2,800);
						beep(1,700);
						beep(10,500);
			
			}else{
				
						char finalScore[5];
						intToBase(score,finalScore,10);
						drawText("YOU LOST! Final Score was ", 400,5 + CHAR_HEIGHT,WHITE,BLACK);
						drawText(finalScore, 400 + 26 * CHAR_WIDTH, 5 + CHAR_HEIGHT,WHITE,BLACK);
						beep(1,2000);
						beep(2,3000);
						beep(1,4000);
						beep(10,5000);
		
			
			}
			savedGame = 0;
			drawText("Press Enter to return to terminal or R to restart",320, 5 + 2*CHAR_HEIGHT,WHITE,BLACK);
			char c;
			while((c = getchar()) != '\n'){
				if(c == RESTART_KEY){
					newGame();
					break;
				}
			}

		}else if(key == SAVE_KEY){
			clearScreen();
			save();
		}else{
			newGame();
		}
	
			clearScreen();
}

static void printTime(){
	char time[5];
	intToBase(gameTimer,time,10);
	drawText("Time: ",5,5,WHITE,BLACK);
	drawText(time,5 + 6*CHAR_WIDTH ,5,WHITE,BLACK);

}


static void update(){
		movePlayer();
		moveBall();
		checkWin();

	
}

static void throwBall(){
	ball.xSpeed = DEFAULT_BALL_X_SPEED;
	ball.ySpeed = DEFAULT_BALL_Y_SPEED;
	if(LEFT){
		ball.xDir = -1;
	}else if(RIGHT){
		ball.xDir = 1;
	}else{
		ball.xDir = -1;
	}
	ball.yDir = -1;
	ball.thrown = 1;
	drawRect(0, 0, SCREEN_WIDTH,100,BLACK);
	startTime = getSeconds();
}

static void keyHandler(char key){
	
			if(key == 'a' || key == 'A'){
					LEFT = 1;
					RIGHT = 0;
		
				}else if(key == 'd' || key == 'D'){
					RIGHT = 1;
					LEFT = 0;
				
				}else if(key == 'r' || key =='R'){
					newGame();
				}else if(key == ' '){
					if(!ball.thrown){
						throwBall();
					}
				}else{
					RIGHT = 0;
					LEFT = 0;
				}
				
	

}



static void moveBall(){

		drawCircle(ball.c.x, ball.c.y, ball.c.radius, BLACK);

		if(!ball.thrown){
			ball.c.x = player.r.x + player.r.width/2;
		}else{
			if(ball.c.y - ball.c.radius <= 0){
				ball.c.y = ball.c.radius;
				ball.yDir *= -1;
			}
			if(ball.c.x - ball.c.radius <= 0 && ball.c.y +ball.c.radius <= SCREEN_HEIGHT - player.r.height){
				ball.c.x = ball.c.radius;
				ball.xDir *=-1;
			}else if(ball.c.x + ball.c.radius >= SCREEN_WIDTH && ball.c.y + ball.c.radius <= SCREEN_HEIGHT - player.r.height){
				ball.c.x = SCREEN_WIDTH - ball.c.radius;
				ball.xDir *=-1;
			}else if(ball.c.y >= SCREEN_HEIGHT){
				gameOver = LOST;
				return;
			}
			checkBallCollisions();
			ball.c.x += ball.xDir * ball.xSpeed;
			ball.c.y += ball.yDir * ball.ySpeed;
		}
		
		drawCircle(ball.c.x, ball.c.y, ball.c.radius, ball.c.color);

		
}

static void checkBallCollisions(){
	
	if(checkRectCollision(player.r)){
		drawRect(player.r.x, player.r.y, player.r.width,player.r.height,player.r.color);
		beep(1,3000);
	}
	for(int i = 0; i< WALL_ROWS;i++){
		for(int j = 0; j < WALL_COLUMNS; j++){
				Wall wall = walls[i][j];
				int hit;
				if(wall.hit == 0){
					hit = checkRectCollision(wall.r);
					if(hit == 1){
						
						walls[i][j].hit = 1;
						score++;
						drawRect(wall.r.x, wall.r.y, wall.r.width,wall.r.height,BLACK);
					}
				}
			
		}
	}

	
}


static int checkRectCollision(Rectangle rec){
	int ballX = ball.c.x;
	int ballY = ball.c.y;
	int radius = ball.c.radius;
	//UP AND DOWN
	if(ballX >= rec.x && ballX <= rec.x + rec.width){
		int isDown = (ballY + radius >= rec.y + rec.height) && (ballY - radius <= rec.y + rec.height);
		int isUp =  ballY - radius <= rec.y && ballY + radius >= rec.y ;
		if(isDown || isUp){
		
			ball.yDir *=-1;
			return 1;
		}
		
	}
	//LEFT AND RIGHT
	if(ballY >= rec.y && ballY <= rec.y + rec.height){
		int isLeft = (ballX - radius <= rec.x) && (ballX + radius >= rec.x);
		int isRight = (ballX + radius >= rec.x + rec.width) && (ballX - radius <= rec.x + rec.width);
		if(isLeft || isRight){
		
			ball.xDir *=-1;
			return 1;
		}
	
	}
	
	return 0;


}
static void movePlayer(){


	if(LEFT && player.r.x >  player.xSpeed){
		player.r.x -= player.xSpeed;
	
		int pos = player.r.x + player.r.width;
		drawRect(pos,player.r.y,player.xSpeed,player.r.height,BLACK);
		}
	if(RIGHT && player.r.x + player.r.width < SCREEN_WIDTH - player.xSpeed){
		player.r.x += player.xSpeed;
		
			int pos = player.r.x - player.xSpeed;
		drawRect(pos,player.r.y,player.xSpeed,player.r.height,BLACK);
	
	}
	drawRect(player.r.x, player.r.y, player.r.width,player.r.height,player.r.color);

}







