#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Network.hpp>
#include <SFML\Window.hpp>
#include <SFML\System.hpp>
#include <iostream>
#include <string>
#include <array>
#include <windows.h>

std::array<sf::Vector2f, 65> Centers;

//Calculating centers of the squaress
std::array<sf::Vector2f, 65>  Centers_calculating(std::array<sf::Vector2f, 65> Centers) {
	for (int i = 1; i < 65; i++) {
		div_t liczba = div(i - 1, 8);
		Centers[i] = sf::Vector2f((liczba.rem * 90.0f) + 100.0f, (liczba.quot * 90.0f) + 10.0f);
	}
	return Centers;
}

class Square {
public:
	int piece;
	sf::Vector2f center;
	int move;
	int is_moving;
	std::vector<sf::Vector2i> toedge;
	Square() {
		piece = 0;
		center = sf::Vector2f(0.0f, 0.0f);
		move = 0;
		is_moving = 0;
		toedge = {};
	}
};

int main() {
	//1600, 1024
	const char startingFEN [44] = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";
	//const char startingFEN[53] = "r3kb1r/1pp2p1p/p4pp1/4n1n1/3P4/2P1P3/P1B2PPP/R1B2RK1";

	//board

	Centers = Centers_calculating(Centers);

	Square* Squares = new Square[65];
	for (int i = 1; i < 65; i++) {
		Squares[i].center = Centers[i];
	}

	sf::RenderWindow window(sf::VideoMode(1366, 768), "Chess", sf::Style::Close | sf::Style::Titlebar);
	sf::RectangleShape darksquare(sf::Vector2f(90.0f, 90.0f));
	sf::RectangleShape lightsquare(sf::Vector2f(90.0f, 90.0f));
	sf::RectangleShape darksquaremove(sf::Vector2f(90.0f, 90.0f));
	sf::RectangleShape lightsquaremove(sf::Vector2f(90.0f, 90.0f));
	sf::RectangleShape darksquareleft(sf::Vector2f(90.0f, 90.0f));
	sf::RectangleShape lightsquareleft(sf::Vector2f(90.0f, 90.0f));
	sf::RectangleShape darksquareattack(sf::Vector2f(90.0f, 90.0f));
	sf::RectangleShape lightsquareattack(sf::Vector2f(90.0f, 90.0f));

	//colors
	darksquare.setFillColor(sf::Color(148, 111, 81));
	lightsquare.setFillColor(sf::Color(240, 217, 181));
	darksquaremove.setFillColor(sf::Color(170, 162, 58));
	lightsquaremove.setFillColor(sf::Color(205, 210, 106));
	darksquareleft.setFillColor(sf::Color(100, 111, 64));
	lightsquareleft.setFillColor(sf::Color(130, 151, 105));
	darksquareattack.setFillColor(sf::Color(206, 46, 34, 140));
	lightsquareattack.setFillColor(sf::Color(241, 27, 10, 140));

	//font
	sf::Font font;

	if (!font.loadFromFile("ArialCE.ttf")) {
		std::cout << "Font load failed!" << std::endl;
	}

	//text
	sf::Text text;
	text.setFont(font);
	text.setString("Checkmate!");
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setPosition(sf::Vector2f(850, 340));

	//creating space for textures
	sf::Texture texture_w_pawn;
	sf::Texture texture_w_rook;
	sf::Texture texture_w_bishop;
	sf::Texture texture_w_knight;
	sf::Texture texture_w_king;
	sf::Texture texture_w_queen;
	sf::Texture texture_b_pawn;
	sf::Texture texture_b_rook;
	sf::Texture texture_b_bishop;
	sf::Texture texture_b_knight;
	sf::Texture texture_b_king;
	sf::Texture texture_b_queen;

	//texture load
	bool status = true;
	if (!texture_w_pawn.loadFromFile("C:/Users/dawig/source/repos/Chess/Textures/Chess_plt60.png")) {
		std::cout << "Texture load Failed!" << std::endl;
		status = false;
	}
	if (!texture_w_rook.loadFromFile("C:/Users/dawig/source/repos/Chess/Textures/Chess_rlt60.png")) {
		std::cout << "Texture load Failed!" << std::endl;
		status = false;
	}
	if (!texture_w_bishop.loadFromFile("C:/Users/dawig/source/repos/Chess/Textures/Chess_blt60.png")) {
		std::cout << "Texture load Failed!" << std::endl;
		status = false;
	}
	if (!texture_w_knight.loadFromFile("C:/Users/dawig/source/repos/Chess/Textures/Chess_nlt60.png")) {
		std::cout << "Texture load Failed!" << std::endl;
		status = false;
	}
	if (!texture_w_king.loadFromFile("C:/Users/dawig/source/repos/Chess/Textures/Chess_klt60.png")) {
		std::cout << "Texture load Failed!" << std::endl;
		status = false;
	}
	if (!texture_w_queen.loadFromFile("C:/Users/dawig/source/repos/Chess/Textures/Chess_qlt60.png")) {
		std::cout << "Texture load Failed!" << std::endl;
		status = false;
	}
	if (!texture_b_pawn.loadFromFile("C:/Users/dawig/source/repos/Chess/Textures/Chess_pdt60.png")) {
		std::cout << "Texture load Failed!" << std::endl;
		status = false;
	}
	if (!texture_b_rook.loadFromFile("C:/Users/dawig/source/repos/Chess/Textures/Chess_rdt60.png")) {
		std::cout << "Texture load Failed!" << std::endl;
		status = false;
	}
	if (!texture_b_bishop.loadFromFile("C:/Users/dawig/source/repos/Chess/Textures/Chess_bdt60.png")) {
		std::cout << "Texture load Failed!" << std::endl;
		status = false;
	}
	if (!texture_b_knight.loadFromFile("C:/Users/dawig/source/repos/Chess/Textures/Chess_ndt60.png")) {
		std::cout << "Texture load Failed!" << std::endl;
		status = false;
	}
	if (!texture_b_king.loadFromFile("C:/Users/dawig/source/repos/Chess/Textures/Chess_kdt60.png")) {
		std::cout << "Texture load Failed!" << std::endl;
		status = false;
	}
	if (!texture_b_queen.loadFromFile("C:/Users/dawig/source/repos/Chess/Textures/Chess_qdt60.png")) {
		std::cout << "Texture load Failed!" << std::endl;
		status = false;
	}

	if (status) {
		std::cout << "Texture load Succesfull!" << std::endl;
	}

	//creating pieces
	sf::Sprite w_pawn;
	sf::Sprite w_rook;
	sf::Sprite w_bishop;
	sf::Sprite w_knight;
	sf::Sprite w_king;
	sf::Sprite w_queen;
	sf::Sprite b_pawn;
	sf::Sprite b_rook;
	sf::Sprite b_bishop;
	sf::Sprite b_knight;
	sf::Sprite b_king;
	sf::Sprite b_queen;

	//texturing pieces
	w_pawn.setTexture(texture_w_pawn);
	w_rook.setTexture(texture_w_rook);
	w_bishop.setTexture(texture_w_bishop);
	w_knight.setTexture(texture_w_knight);
	w_king.setTexture(texture_w_king);
	w_queen.setTexture(texture_w_queen);
	b_pawn.setTexture(texture_b_pawn);
	b_rook.setTexture(texture_b_rook);
	b_bishop.setTexture(texture_b_bishop);
	b_knight.setTexture(texture_b_knight);
	b_king.setTexture(texture_b_king);
	b_queen.setTexture(texture_b_queen);

	//scaleing the pieces
	w_pawn.setScale(1.5f, 1.5f);
	w_rook.setScale(1.5f, 1.5f);
	w_bishop.setScale(1.5f, 1.5f);
	w_knight.setScale(1.5f, 1.5f);
	w_king.setScale(1.5f, 1.5f);
	w_queen.setScale(1.5f, 1.5f);
	b_pawn.setScale(1.5f, 1.5f);
	b_rook.setScale(1.5f, 1.5f);
	b_bishop.setScale(1.5f, 1.5f);
	b_knight.setScale(1.5f, 1.5f);
	b_king.setScale(1.5f, 1.5f);
	b_queen.setScale(1.5f, 1.5f);

	texture_w_pawn.setSmooth(true);
	texture_w_rook.setSmooth(true);
	texture_w_bishop.setSmooth(true);
	texture_w_knight.setSmooth(true);
	texture_w_king.setSmooth(true);
	texture_w_queen.setSmooth(true);
	texture_b_pawn.setSmooth(true);
	texture_b_rook.setSmooth(true);
	texture_b_bishop.setSmooth(true);
	texture_b_knight.setSmooth(true);
	texture_b_king.setSmooth(true);
	texture_b_queen.setSmooth(true);

	//variables
	bool start = true;
	bool calculated = false;
	bool mate = false;
	int moving_piece = 0;
	int turn = 0;
	int oldsquare = 0;
	int klatka = 0;

	std::vector<int> moves;
	std::vector<int> legal_moves;

	std::vector<int> calculatemoves(int, std::vector<sf::Vector2i>, Square[65], int);
	std::vector<int> calculate_check(Square[65], std::vector<int>, int, int, int);
	bool is_checkmate(Square[65], int);

	while (window.isOpen()) {

		sf::Event evnt;

		sf::Vector2i pos = sf::Mouse::getPosition(window);
		int x = ceil((pos.x - 100) / 90) + 1;
		int y = ceil((pos.y - 10) / 90) + 1;

		while (window.pollEvent(evnt)) {

			if (evnt.type == evnt.Closed) {
				window.close();
			}

			if (evnt.type == evnt.MouseButtonPressed) {
				if (evnt.key.code == sf::Mouse::Left) {

					//transformation

					//is there some piece?
					int position = 8 * (y-1) + x;
					calculated = false;
					if (Squares[position].piece != 0) {
						oldsquare = position;
						if (Squares[position].piece == 9 && turn == 0) {
							Squares[position].is_moving = Squares[position].piece;
							Squares[position].piece = 0;
							moving_piece = 9;
						}
						if (Squares[position].piece == 10 && turn == 0) {
							Squares[position].is_moving = Squares[position].piece;
							Squares[position].piece = 0;
							moving_piece = 10;
						}
						if (Squares[position].piece == 11 && turn == 0) {
							Squares[position].is_moving = Squares[position].piece;
							Squares[position].piece = 0;
							moving_piece = 11;
						}
						if (Squares[position].piece == 12 && turn == 0) {
							Squares[position].is_moving = Squares[position].piece;
							Squares[position].piece = 0;
							moving_piece = 12;
						}
						if (Squares[position].piece == 13 && turn == 0) {
							Squares[position].is_moving = Squares[position].piece;
							Squares[position].piece = 0;
							moving_piece = 13;
						}
						if (Squares[position].piece == 14 && turn == 0) {
							Squares[position].is_moving = Squares[position].piece;
							Squares[position].piece = 0;
							moving_piece = 14;
						}
						if (Squares[position].piece == 17 && turn == 1) {
							Squares[position].is_moving = Squares[position].piece;
							Squares[position].piece = 0;
							moving_piece = 17;
						}
						if (Squares[position].piece == 18 && turn == 1) {
							Squares[position].is_moving = Squares[position].piece;
							Squares[position].piece = 0;
							moving_piece = 18;
						}
						if (Squares[position].piece == 19 && turn == 1) {
							Squares[position].is_moving = Squares[position].piece;
							Squares[position].piece = 0;
							moving_piece = 19;
						}
						if (Squares[position].piece == 20 && turn == 1) {
							Squares[position].is_moving = Squares[position].piece;
							Squares[position].piece = 0;
							moving_piece = 20;
						}
						if (Squares[position].piece == 21 && turn == 1) {
							Squares[position].is_moving = Squares[position].piece;
							Squares[position].piece = 0;
							moving_piece = 21;
						}
						if (Squares[position].piece == 22 && turn == 1) {
							Squares[position].is_moving = Squares[position].piece;
							Squares[position].piece = 0;
							moving_piece = 22;
						}
					}
				}
			}

			//move
			if (evnt.type == evnt.MouseButtonReleased) {
				if (moving_piece != 0) {
					if (pos.x < 100 or pos.x > 900 or pos.y < 10 or pos.y > 810) {
						Squares[oldsquare].piece = moving_piece;
					}
					else {
						int position = 8 * (y - 1) + x;
						bool moved = false;
						if (moving_piece != Squares[position].is_moving) {
							for (unsigned int i = 0; i < legal_moves.size(); i++) {
								if (position == legal_moves[i]) {
									if (moving_piece == 9) {
										if (position - oldsquare == -2) {
											Squares[57].piece = 0;
											Squares[57].move = 1;
											Squares[60].piece = 13;
										}
										if (position - oldsquare == 2) {
											Squares[64].piece = 0;
											Squares[64].move = 1;
											Squares[62].piece = 13;
										}
									}
									if (moving_piece == 17) {
										if (position - oldsquare == -2) {
											Squares[1].piece = 0;
											Squares[1].move = 1;
											Squares[4].piece = 21;
										}
										if (position - oldsquare == 2) {
											Squares[8].piece = 0;
											Squares[8].move = 1;
											Squares[6].piece = 21;
										}
									}
									moved = true;
									Squares[position].piece = moving_piece;
									Squares[position].move = 1;
									Squares[oldsquare].move = 1;
									Squares[position].toedge = Squares[oldsquare].toedge;
									Squares[position].piece = moving_piece;
									if (turn == 0) {
										turn = 1;
										mate = is_checkmate(Squares, turn);
										if (mate == true) {
											std::cout << "Checkmate" << std::endl;
											text.setFillColor(sf::Color::White);
										}
									}
									else {
										turn = 0;
										mate = is_checkmate(Squares, turn);
										if (mate == true) {
											std::cout << "Checkmate" << std::endl;
											text.setFillColor(sf::Color::White);
										}
									}
									break;
								}
							}
							if (!moved) {
								Squares[oldsquare].piece = moving_piece;
							}
						}
						else {
							Squares[oldsquare].piece = moving_piece;
						}
					}
				}
				moving_piece = 0;
				oldsquare = 0;
				for (int i = 1; i < 65; i++) {
					if (Squares[i].is_moving != 0) {
						Squares[i].is_moving = 0;
					}
				}
			}
		}

		//drawing a board

		for (int i = 1; i < 65; i++) {
			div_t liczba = div(i-1, 8);
			if (liczba.quot % 2 == 0) {
				if (i % 2 == 0) {
					darksquare.setPosition(((i - 1) % 8 * 90.0f) + 100.0f, (liczba.quot * 90.0f) + 10.0f);
					window.draw(darksquare);

				}
				else {
					lightsquare.setPosition(((i - 1) % 8 * 90.0f) + 100.0f, (liczba.quot * 90.0f) + 10.0f);
					window.draw(lightsquare);
				}
			}
			else {
				if (i % 2 != 0) {
					darksquare.setPosition(((i - 1) % 8 * 90.0f) + 100.0f, (liczba.quot * 90.0f) + 10.0f);
					window.draw(darksquare);
				}
				else {
					lightsquare.setPosition(((i - 1) % 8 * 90.0f) + 100.0f, (liczba.quot * 90.0f) + 10.0f);
					window.draw(lightsquare);
				}
			}
			Centers[i] = sf::Vector2f(((i - 1) % 8 * 90.0f) + 145.0f, (liczba.quot * 90.0f) + 55.0f);
		}

		//first loading of the board from FEN

		if (start) {
			char c = '/';

			for (int i = 1; i < 65; i++) {
				for (unsigned int k = 0; k < strlen(startingFEN); k++) {
					if (isdigit(startingFEN[k])) {
						i += startingFEN[k] - 48;
					}
					if (startingFEN[k] == c) {
					}
					if (isalpha(startingFEN[k])) {
						div_t liczba = div(i - 1, 8);
						char letter = startingFEN[k];
						if (letter == *"P") {
							w_pawn.setPosition((liczba.rem * 90.0f) + 100.0f, (liczba.quot * 90.0f) + 10.0f);
							window.draw(w_pawn);
							if (i < 48 or i > 56) {
								Squares[i].move = 1;
							}
							Squares[i].piece = 10;
							Squares[i].toedge = {
								sf::Vector2i(-8, 0),
								sf::Vector2i(-7, 0),
								sf::Vector2i(-9, 0)
							};
						}
						if (letter == *"R") {
							w_rook.setPosition((liczba.rem * 90.0f) + 100.0f, (liczba.quot * 90.0f) + 10.0f);
							window.draw(w_rook);
							Squares[i].piece = 13;
							Squares[i].toedge = {
								sf::Vector2i(-8, 0),
								sf::Vector2i(1, 0),
								sf::Vector2i(-8, 0),
								sf::Vector2i(-1, 0)
							};
						}
						if (letter == *"B") {
							w_bishop.setPosition((liczba.rem * 90.0f) + 100.0f, (liczba.quot * 90.0f) + 10.0f);
							window.draw(w_bishop);
							Squares[i].piece = 12;
							Squares[i].toedge = {
								sf::Vector2i(-9, 0),
								sf::Vector2i(9, 0),
								sf::Vector2i(7, 0),
								sf::Vector2i(-7, 0)
							};
						}
						if (letter == *"N") {
							w_knight.setPosition((liczba.rem * 90.0f) + 100.0f, (liczba.quot * 90.0f) + 10.0f);
							window.draw(w_knight);
							Squares[i].piece = 11;
							Squares[i].toedge = {
								sf::Vector2i(-15, 0),
								sf::Vector2i(-6, 0),
								sf::Vector2i(10, 0),
								sf::Vector2i(17, 0),
								sf::Vector2i(15, 0),
								sf::Vector2i(6, 0),
								sf::Vector2i(-10, 0),
								sf::Vector2i(-17, 0),
							};
						}
						if (letter == *"K") {
							w_king.setPosition((liczba.rem * 90.0f) + 100.0f, (liczba.quot * 90.0f) + 10.0f);
							window.draw(w_king);
							Squares[i].piece = 9;
							Squares[i].toedge = {
								sf::Vector2i(-8, 0),
								sf::Vector2i(-7, 0),
								sf::Vector2i(1, 0),
								sf::Vector2i(9, 0),
								sf::Vector2i(8, 0),
								sf::Vector2i(7, 0),
								sf::Vector2i(-1, 0),
								sf::Vector2i(-9, 0)
							};
						}
						if (letter == *"Q") {
							w_queen.setPosition((liczba.rem * 90.0f) + 100.0f, (liczba.quot * 90.0f) + 10.0f);
							window.draw(w_queen);
							Squares[i].piece = 14;
							Squares[i].toedge = {
								sf::Vector2i(-8, 0),
								sf::Vector2i(-7, 0),
								sf::Vector2i(1, 0),
								sf::Vector2i(9, 0),
								sf::Vector2i(8, 0),
								sf::Vector2i(7, 0),
								sf::Vector2i(-1, 0),
								sf::Vector2i(-9, 0)
							};
						}
						if (letter == *"p") {
							b_pawn.setPosition((liczba.rem * 90.0f) + 100.0f, (liczba.quot * 90.0f) + 10.0f);
							window.draw(b_pawn);
							Squares[i].piece = 18;
							if (i < 9 or i > 16) {
								Squares[i].move = 1;
							}
							Squares[i].toedge = {
								sf::Vector2i(8, 0),
								sf::Vector2i(7, 0),
								sf::Vector2i(9, 0)
							};
						}
						if (letter == *"r") {
							b_rook.setPosition((liczba.rem * 90.0f) + 100.0f, (liczba.quot * 90.0f) + 10.0f);
							window.draw(b_rook);
							Squares[i].piece = 21;
							Squares[i].toedge = {
								sf::Vector2i(-8, 0),
								sf::Vector2i(1, 0),
								sf::Vector2i(-8, 0),
								sf::Vector2i(-1, 0)
							};
						}
						if (letter == *"n") {
							b_knight.setPosition((liczba.rem * 90.0f) + 100.0f, (liczba.quot * 90.0f) + 10.0f);
							window.draw(b_knight);
							Squares[i].piece = 19;
							Squares[i].toedge = {
								sf::Vector2i(-15, 0),
								sf::Vector2i(-6, 0),
								sf::Vector2i(10, 0),
								sf::Vector2i(17, 0),
								sf::Vector2i(15, 0),
								sf::Vector2i(6, 0),
								sf::Vector2i(-10, 0),
								sf::Vector2i(-17, 0),
							};
						}
						if (letter == *"b") {
							b_bishop.setPosition((liczba.rem * 90.0f) + 100.0f, (liczba.quot * 90.0f) + 10.0f);
							window.draw(b_bishop);
							Squares[i].piece = 20;
							Squares[i].toedge = {
								sf::Vector2i(-9, 0),
								sf::Vector2i(9, 0),
								sf::Vector2i(7, 0),
								sf::Vector2i(-7, 0)
							};
						}
						if (letter == *"k") {
							b_king.setPosition((liczba.rem * 90.0f) + 100.0f, (liczba.quot * 90.0f) + 10.0f);
							window.draw(b_king);
							Squares[i].piece = 17;
							Squares[i].toedge = {
								sf::Vector2i(-8, 0),
								sf::Vector2i(-7, 0),
								sf::Vector2i(1, 0),
								sf::Vector2i(9, 0),
								sf::Vector2i(8, 0),
								sf::Vector2i(7, 0),
								sf::Vector2i(-1, 0),
								sf::Vector2i(-9, 0)
							};
						}
						if (letter == *"q") {
							b_queen.setPosition((liczba.rem * 90.0f) + 100.0f, (liczba.quot * 90.0f) + 10.0f);
							window.draw(b_queen);
							Squares[i].piece = 22;
							Squares[i].toedge = {
								sf::Vector2i(-8, 0),
								sf::Vector2i(-7, 0),
								sf::Vector2i(1, 0),
								sf::Vector2i(9, 0),
								sf::Vector2i(8, 0),
								sf::Vector2i(7, 0),
								sf::Vector2i(-1, 0),
								sf::Vector2i(-9, 0)
							};
						}
						i++;
					}

				}
			}
			start = false;
		}

		//loading pieces from memory

		if (!start) {
			for (int i = 1; i < 65; i++) {
				div_t liczba = div(i - 1, 8);
				sf::Vector2f pole;
				pole.x = (liczba.rem * 90.0f) + 100.0f;
				pole.y = (liczba.quot * 90.0f) + 10.0f;
				switch (Squares[i].piece) {
				case 0:
					continue;
				case 9:
					w_king.setPosition(pole);
					window.draw(w_king);
					break;
				case 10:
					w_pawn.setPosition(pole);
					window.draw(w_pawn);
					break;
				case 11:
					w_knight.setPosition(pole);
					window.draw(w_knight);
					break;
				case 12:
					w_bishop.setPosition(pole);
					window.draw(w_bishop);
					break;
				case 13:
					w_rook.setPosition(pole);
					window.draw(w_rook);
					break;
				case 14:
					w_queen.setPosition(pole);
					window.draw(w_queen);
					break;
				case 17:
					b_king.setPosition(pole);
					window.draw(b_king);
					break;
				case 18:
					b_pawn.setPosition(pole);
					window.draw(b_pawn);
					break;
				case 19:
					b_knight.setPosition(pole);
					window.draw(b_knight);
					break;
				case 20:
					b_bishop.setPosition(pole);
					window.draw(b_bishop);
					break;
				case 21:
					b_rook.setPosition(pole);
					window.draw(b_rook);
					break;
				case 22:
					b_queen.setPosition(pole);
					window.draw(b_queen);
					break;
				}
			}
		}

		//drawing the piece where he left the square

		for (int i = 1; i < 65; i++) {
			if (Squares[i].is_moving != 0) {
				div_t liczba = div(i - 1, 8);
				if ((i + liczba.quot) % 2 != 0) {
					lightsquareleft.setPosition(Squares[i].center);
					window.draw(lightsquareleft);
				}
				else {
					darksquareleft.setPosition(Squares[i].center);
					window.draw(darksquareleft);
				}
				if (Squares[i].is_moving == 9) {
					w_king.setColor(sf::Color(255, 255, 255, 140));
					w_king.setPosition(Squares[i].center);
					window.draw(w_king);
					w_king.setColor(sf::Color(255, 255, 255, 255));
				}
				if (Squares[i].is_moving == 10) {
					w_pawn.setColor(sf::Color(255, 255, 255, 140));
					w_pawn.setPosition(Squares[i].center);
					window.draw(w_pawn);
					w_pawn.setColor(sf::Color(255, 255, 255, 255));
				}
				if (Squares[i].is_moving == 11) {
					w_knight.setColor(sf::Color(255, 255, 255, 140));
					w_knight.setPosition(Squares[i].center);
					window.draw(w_knight);
					w_knight.setColor(sf::Color(255, 255, 255, 255));
				}
				if (Squares[i].is_moving == 12) {
					w_bishop.setColor(sf::Color(255, 255, 255, 140));
					w_bishop.setPosition(Squares[i].center);
					window.draw(w_bishop);
					w_bishop.setColor(sf::Color(255, 255, 255, 255));
				}
				if (Squares[i].is_moving == 13) {
					w_rook.setColor(sf::Color(255, 255, 255, 140));
					w_rook.setPosition(Squares[i].center);
					window.draw(w_rook);
					w_rook.setColor(sf::Color(255, 255, 255, 255));
				}
				if (Squares[i].is_moving == 14) {
					w_queen.setColor(sf::Color(255, 255, 255, 140));
					w_queen.setPosition(Squares[i].center);
					window.draw(w_queen);
					w_queen.setColor(sf::Color(255, 255, 255, 255));
				}
				if (Squares[i].is_moving == 17) {
					b_king.setColor(sf::Color(255, 255, 255, 140));
					b_king.setPosition(Squares[i].center);
					window.draw(b_rook);
					b_king.setColor(sf::Color(255, 255, 255, 255));
				}
				if (Squares[i].is_moving == 18) {
					b_pawn.setColor(sf::Color(255, 255, 255, 140));
					b_pawn.setPosition(Squares[i].center);
					window.draw(b_pawn);
					b_pawn.setColor(sf::Color(255, 255, 255, 255));
				}
				if (Squares[i].is_moving == 19) {
					b_knight.setColor(sf::Color(255, 255, 255, 140));
					b_knight.setPosition(Squares[i].center);
					window.draw(b_knight);
					b_knight.setColor(sf::Color(255, 255, 255, 255));
				}
				if (Squares[i].is_moving == 20) {
					b_bishop.setColor(sf::Color(255, 255, 255, 140));
					b_bishop.setPosition(Squares[i].center);
					window.draw(b_bishop);
					b_bishop.setColor(sf::Color(255, 255, 255, 255));
				}
				if (Squares[i].is_moving == 21) {
					b_rook.setColor(sf::Color(255, 255, 255, 140));
					b_rook.setPosition(Squares[i].center);
					window.draw(b_rook);
					b_rook.setColor(sf::Color(255, 255, 255, 255));
				}
				if (Squares[i].is_moving == 22) {
					b_queen.setColor(sf::Color(255, 255, 255, 140));
					b_queen.setPosition(Squares[i].center);
					window.draw(b_queen);
					b_queen.setColor(sf::Color(255, 255, 255, 255));
				}
			}
		}

		//calculating possible moves
		if (moving_piece != 0) {
			if (!calculated) {
				moves = calculatemoves(oldsquare, Squares[oldsquare].toedge, Squares, moving_piece);
				legal_moves = calculate_check(Squares, moves, turn, oldsquare, moving_piece);
				calculated = true;
			}
			for (unsigned int i = 0; i < legal_moves.size(); i++) {
				darksquareattack.setPosition(sf::Vector2f(Squares[legal_moves[i]].center));
				window.draw(darksquareattack);
			}
		}
		

		//drawing moving piece on coursor

		if (moving_piece != 0) {
			if (moving_piece == 9) {
				w_king.setPosition(sf::Vector2f(pos.x - 45.0f, pos.y - 45.0f));
				window.draw(w_king);
			}
			if (moving_piece == 10) {
				w_pawn.setPosition(sf::Vector2f(pos.x - 45.0f, pos.y - 45.0f));
				window.draw(w_pawn);
			}
			if (moving_piece == 11) {
				w_knight.setPosition(sf::Vector2f(pos.x - 45.0f, pos.y - 45.0f));
				window.draw(w_knight);
			}
			if (moving_piece == 12) {
				w_bishop.setPosition(sf::Vector2f(pos.x - 45.0f, pos.y - 45.0f));
				window.draw(w_bishop);
			}
			if (moving_piece == 13) {
				w_rook.setPosition(sf::Vector2f(pos.x - 45.0f, pos.y - 45.0f));
				window.draw(w_rook);
			}
			if (moving_piece == 14) {
				w_queen.setPosition(sf::Vector2f(pos.x - 45.0f, pos.y - 45.0f));
				window.draw(w_queen);
			}
			if (moving_piece == 17) {
				b_king.setPosition(sf::Vector2f(pos.x - 45.0f, pos.y - 45.0f));
				window.draw(b_king);
			}
			if (moving_piece == 18) {
				b_pawn.setPosition(sf::Vector2f(pos.x - 45.0f, pos.y - 45.0f));
				window.draw(b_pawn);
			}
			if (moving_piece == 19) {
				b_knight.setPosition(sf::Vector2f(pos.x - 45.0f, pos.y - 45.0f));
				window.draw(b_knight);
			}
			if (moving_piece == 20) {
				b_bishop.setPosition(sf::Vector2f(pos.x - 45.0f, pos.y - 45.0f));
				window.draw(b_bishop);
			}
			if (moving_piece == 21) {
				b_rook.setPosition(sf::Vector2f(pos.x - 45.0f, pos.y - 45.0f));
				window.draw(b_rook);
			}
			if (moving_piece == 22) {
				b_queen.setPosition(sf::Vector2f(pos.x - 45.0f, pos.y - 45.0f));
				window.draw(b_queen);
			}
		}
		if (mate == true) {
			window.draw(text);
		}

		window.display();
		//Sleep(1000000);
		window.clear(sf::Color::Black);

		//klatka += 1;
		//std::cout << "Koniec klatki " << klatka;
	}

	return 0;
}


std::vector<int> calculatemoves(int square, std::vector<sf::Vector2i> toedge, Square Squares[65], int piece) {
	std::vector <int> result;
	int original_square = square;
	bool koniec = false;
	for (unsigned int i = 0; i < toedge.size(); i++) {
		square = original_square;
		div_t liczba = div (square - 1, 8);
		int file = liczba.rem + 1;
		int oldfile = file;
		while (true) {
			square = square + toedge[i].x;
			div_t liczba = div(square - 1, 8);
			file = liczba.rem + 1;
			if (square < 0 or square > 64) {
				break;
			}
			if (abs(file - oldfile) > 2) {
				break;
			}
			if (piece < 16 && Squares[square].piece < 16 && Squares[square].piece > 0) {
				break;
			}
			else if (piece < 16 && Squares[square].piece > 16 && piece != 10 && piece != 18) {
				result.push_back(square);
				break;
			}
			else if (piece > 16 && Squares[square].piece > 16) {
				break;
			}
			else if (piece > 16 && Squares[square].piece < 16 && Squares[square].piece > 0 && piece != 10 && piece != 18) {
				result.push_back(square);
				break;
			}
			if (Squares[square].piece == 0) {
				result.push_back(square);
			}
			if (piece == 9 or piece == 11 or piece == 17 or piece == 19) {
				break;
			}
			if (koniec) {
				i = 2;
				break;
			}
			if ((piece == 10 or piece == 18) && Squares[original_square].move == 1) {
				i = 2;
				break;
			}
			if ((piece == 10 or piece == 18) && Squares[original_square].move == 0) {
				koniec = true;
			}
			oldfile = file;
		}
	}
	if (piece == 10 or piece == 18) {
		for (int i = 1; i < 3; i++) {
			square = original_square;
			square = square + toedge[i].x;
			if (piece < 16 && Squares[square].piece > 16) {
				result.push_back(square);
			}
			if (piece > 16 && Squares[square].piece < 16 && Squares[square].piece > 0) {
				result.push_back(square);
			}
		}
	}
	if (piece == 9) {
		square = original_square;
		if (square == 61 && Squares[square].move == 0) {
			if (Squares[64].piece == 13 && Squares[64].move == 0) {
				bool okay = true;
				for (int i = 62; i < 64; i++) {
					if (Squares[i].piece != 0) {
						okay = false;
					}
				}
				if (okay) {
					result.push_back(square + 2);
				}
			}
			if (Squares[57].piece == 13 && Squares[57].move == 0) {
				bool okay = true;
				for (int i = 58; i < 61; i++) {
					if (Squares[i].piece != 0) {
						okay = false;
					}
				}
				if (okay) {
					result.push_back(square - 2);
				}
			}
		}
	}
	if (piece == 17) {
		square = original_square;
		if (square == 5 && Squares[square].move == 0) {
			if (Squares[8].piece == 21 && Squares[8].move == 0) {
				bool okay = true;
				for (int i = 6; i < 8; i++) {
					if (Squares[i].piece != 0) {
						okay = false;
					}
				}
				if (okay) {
					result.push_back(square);
				}
			}
			if (Squares[1].piece == 21 && Squares[1].move == 0) {
				bool okay = true;
				for (int i = 1; i < 5; i++) {
					if (Squares[i].piece != 0) {
						okay = false;
					}
				}
				if (okay) {
					result.push_back(square);
				}
			}
		}
	}

	return result;
}

std::vector<int> calculate_check(Square Squares[65],std::vector<int> moves, int turn, int square, int piece) {
	std::vector<int> checks;
	std::vector<int> to_delete;
	int original_piece;
	int number = 0;
	if (turn == 0) {
		for (unsigned int n = 0; n < moves.size(); n++) {
			square = moves[n];
			original_piece = Squares[square].piece;
			Squares[square].piece = piece;
			for (int i = 1; i < 65; i++) {
				if (Squares[i].piece > 16) {
					checks = calculatemoves(i, Squares[i].toedge, Squares, Squares[i].piece);
					for (unsigned int z = 0; z < checks.size(); z++) {
						if (Squares[checks[z]].piece == 9) {
							to_delete.push_back(moves[n]);
						}
					}
				}
			}
			Squares[square].piece = original_piece;
		}
	}
	if (turn == 1) {
		for (unsigned int n = 0; n < moves.size(); n++) {
			square = moves[n];
			original_piece = Squares[square].piece;
			Squares[square].piece = piece;
			for (int i = 1; i < 65; i++) {
				if (Squares[i].piece < 16 && Squares[i].piece != 0) {
					checks = calculatemoves(i, Squares[i].toedge, Squares, Squares[i].piece);
					for (unsigned int z = 0; z < checks.size(); z++) {
						if (Squares[checks[z]].piece == 17) {
							to_delete.push_back(moves[n]);
						}
					}
				}
			}
			Squares[square].piece = original_piece;
		}
	}
	for (unsigned int q = 0; q < to_delete.size(); q++) {
		for (unsigned int i = 0; i < moves.size(); i++) {
			if (moves[i] == to_delete[q]) {
				number = i;
				break;
			}
		}
		if (moves.size() != 0) {
			moves.erase(moves.begin() + number);
		}
	}
	return moves;
}

bool is_checkmate(Square Squares[65], int turn) {
	std::vector<int> moves1;
	std::vector<int> legal_moves1;
	int number = 0;
	bool is_mate = true;
	for (int i = 1; i < 65; i++) {
		if (turn == 0) {
			if (Squares[i].piece < 16 && Squares[i].piece != 0) {
				moves1 = calculatemoves(i, Squares[i].toedge, Squares, Squares[i].piece);
				legal_moves1 = calculate_check(Squares, moves1, turn, i, Squares[i].piece);
				if (legal_moves1.size() > 0) {
					is_mate = false;
				}
			}
		}
		if (turn == 1) {
			if (Squares[i].piece > 16) {
				moves1 = calculatemoves(i, Squares[i].toedge, Squares, Squares[i].piece);
				legal_moves1 = calculate_check(Squares, moves1, turn, i, Squares[i].piece);
				if (legal_moves1.size() > 0) {
					is_mate = false;
				}
			}
		}
	}
	return is_mate;
}
