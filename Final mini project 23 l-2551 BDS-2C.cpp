#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <chrono>

class Cell {
private:
    bool isMine;
    bool isFlagged;
    int adjacentMines;

public:
    bool isExposed;
    Cell() : isMine(false), isExposed(false), isFlagged(false), adjacentMines(0) {}

    void setMine() {
        isMine = true;
    }

    bool getMineStatus() const {
        return isMine;
    }

    void expose() {
        isExposed = true;
    }

    bool isCellExposed() const {
        return isExposed;
    }

    void toggleFlag() {
        isFlagged = !isFlagged;
    }

    bool isCellFlagged() const {
        return isFlagged;
    }

    void setAdjacentMines(int count) {
        adjacentMines = count;
    }

    int getAdjacentMines() const {
        return adjacentMines;
    }

    bool getIsExposed() const {
        return isExposed;
    }
};

class Board {
private:
    std::vector<std::vector<Cell>> cells;
    int numRows;
    int numCols;
    int numMines;

public:
    Board(int rows, int cols, int mines) : numRows(rows), numCols(cols), numMines(mines) {
        cells.resize(rows, std::vector<Cell>(cols));
        placeMinesRandomly();
        updateAdjacentMines();
    }

    void placeMinesRandomly() {
        srand(time(nullptr));
        int minesPlaced = 0;
        while (minesPlaced < numMines) {
            int randRow = rand() % numRows;
            int randCol = rand() % numCols;
            if (!cells[randRow][randCol].getMineStatus()) {
                cells[randRow][randCol].setMine();
                minesPlaced++;
            }
        }
    }

    void display(bool showMines = false, int highlightedRow = -1, int highlightedCol = -1) const {
        std::cout << "  ";
        for (int i = 0; i < numCols; i++) {
            std::cout << i << " ";
        }
        std::cout << std::endl;
        for (int i = 0; i < numRows; i++) {
            std::cout << i << " ";
            for (int j = 0; j < numCols; j++) {
                if (cells[i][j].isCellExposed()) {
                    if (cells[i][j].getMineStatus()) {
                        if (i == highlightedRow && j == highlightedCol) {
                            std::cout << "M*"; // Highlighted mine cell
                        }
                        else {
                            std::cout << "* "; // Normal mine cell
                        }
                    }
                    else if (cells[i][j].getAdjacentMines() > 0) {
                        std::cout << cells[i][j].getAdjacentMines() << " ";
                    }
                    else {
                        std::cout << "  ";
                    }
                }
                else if (showMines && cells[i][j].getMineStatus()) {
                    std::cout << "* "; // Show hidden mine cell
                }
                else if (cells[i][j].isCellFlagged()) {
                    std::cout << "F "; // Show flagged cell
                }
                else {
                    std::cout << "X "; // Show hidden non-mine cell
                }
            }
            std::cout << std::endl;
        }
    }

    void updateAdjacentMines() {
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if (!cells[i][j].getMineStatus()) {
                    int count = countAdjacentMines(i, j);
                    cells[i][j].setAdjacentMines(count);
                }
            }
        }
    }

    int countAdjacentMines(int row, int col) const {
        int count = 0;
        for (int i = row - 1; i <= row + 1; i++) {
            for (int j = col - 1; j <= col + 1; j++) {
                if (i >= 0 && i < numRows && j >= 0 && j < numCols && cells[i][j].getMineStatus()) {
                    count++;
                }
            }
        }
        return count;
    }

    bool isGameOver() const {
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if (cells[i][j].isCellExposed() && cells[i][j].getMineStatus()) {
                    return true;
                }
            }
        }
        return false;
    }

    void processMove(int row, int col, char clickType) {
        if (row >= 0 && row < numRows && col >= 0 && col < numCols) {
            if (clickType == 'L') {
                if (!cells[row][col].isCellFlagged() && !cells[row][col].isCellExposed()) {
                    exposeCell(row, col);
                }
            }
            else if (clickType == 'R') {
                if (!cells[row][col].isCellExposed()) {
                    cells[row][col].toggleFlag();
                    if (cells[row][col].isCellFlagged()) {
                        numMines--;
                    }
                    else {
                        numMines++;
                    }
                }
            }
        }
    }

    void exposeCell(int row, int col) {
        if (!cells[row][col].getIsExposed()) {
            cells[row][col].expose();
        }

        if (cells[row][col].getMineStatus()) {
            for (int i = 0; i < numRows; i++) {
                for (int j = 0; j < numCols; j++) {
                    if (cells[i][j].getMineStatus() || cells[i][j].isCellExposed()) {
                        cells[i][j].expose();
                    }
                    else {
                        cells[i][j].isExposed = false;
                    }
                }
            }
            return;
        }

        if (cells[row][col].getAdjacentMines() == 0) {
            for (int i = row - 1; i <= row + 1; i++) {
                for (int j = col - 1; j <= col + 1; j++) {
                    if (i >= 0 && i < numRows && j >= 0 && j < numCols) {
                        if (!cells[i][j].isCellExposed() && !cells[i][j].getMineStatus()) {
                            exposeCell(i, j);
                        }
                    }
                }
            }
        }
    }

    bool checkWin() const {
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                if (!cells[i][j].isCellExposed() && !cells[i][j].getMineStatus()) {
                    return false;
                }
            }
        }
        return true;
    }

    int getNumMines() const {
        return numMines;
    }
};

class Level {
public:
    virtual int getRows() const = 0;
    virtual int getCols() const = 0;
    virtual int getMines() const = 0;
};

class EasyLevel : public Level {
public:
    int getRows() const override {
        return 9;
    }

    int getCols() const override {
        return 9;
    }

    int getMines() const override {
        return 10;
    }
};

class IntermediateLevel : public Level {
public:
    int getRows() const override {
        return 16;
    }

    int getCols() const override {
        return 16;
    }

    int getMines() const override {
        return 40;
    }
};

class AdvancedLevel : public Level {
public:
    int getRows() const override {
        return 22;
    }

    int getCols() const override {
        return 32;
    }

    int getMines() const override {
        return 99;
    }
};

class Player {
private:
    std::string name;
    int score;

public:
    Player(const std::string& playerName) : name(playerName), score(0) {}

    void increaseScore(int points) {
        score += points;
    }

    int getScore() const {
        return score;
    }

    const std::string& getName() const {
        return name;
    }
};

class Playable {
public:
    virtual void startGame() = 0;
    virtual void play() = 0;
};

class Game : public Playable {
private:
    Board board;
    Player player;
    bool isGameWon;
    bool isGameLost;
    std::chrono::time_point<std::chrono::steady_clock> startTime;

public:
    Game(const Level& level, const std::string& playerName)
        : board(level.getRows(), level.getCols(), level.getMines()),
        player(playerName),
        isGameWon(false),
        isGameLost(false) {}

    void startGame() override {
        board.display();
        std::cout << "Number of Mines: " << board.getNumMines() << std::endl;
        std::cout << "Timer: 0 seconds" << std::endl;
        std::cout << "Game started! Enter your moves as 'row column click_type (L for left, R for right):" << std::endl;
        startTime = std::chrono::steady_clock::now(); // Start the timer
    }

    void play() override {
        startGame();
        while (!isGameWon && !isGameLost) {
            int row, col;
            char clickType;
            std::cin >> row >> col >> clickType;
            if (clickType == 'L' || clickType == 'R') { // Validate clickType
                board.processMove(row, col, clickType);
                if (clickType == 'L' && board.isGameOver()) {
                    board.display(true, row, col); // Highlight the selected mine cell
                }
                else {
                    board.display();
                }
                std::cout << "Number of Mines: " << board.getNumMines() << std::endl;
                auto endTime = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
                std::cout << "Timer: " << duration.count() << " seconds" << std::endl;
                if (board.isGameOver()) {
                    isGameLost = true;
                    std::cout << "Game over! You clicked on a mine." << std::endl;
                    break;
                }
                if (board.checkWin()) {
                    isGameWon = true;
                    std::cout << "Congratulations! You won the game." << std::endl;
                    player.increaseScore(100); // Increase player's score for winning
                    std::cout << "Player: " << player.getName() << ", Score: " << player.getScore() << std::endl;
                    break;
                }
            }
            else {
                std::cout << "Invalid click type. Please enter 'L' for left click or 'R' for right click." << std::endl;
            }
        }
        auto endTime = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::seconds>(endTime - startTime);
        std::cout << "Game duration: " << duration.count() << " seconds." << std::endl;
    }
};

int main() {
    std::string playerName;
    std::cout << "Enter your name: ";
    std::cin >> playerName;

    int levelChoice;
    std::cout << "Select difficulty level (1 - Easy, 2 - Intermediate, 3 - Advanced): ";
    std::cin >> levelChoice;

    Level* level = nullptr;
    if (levelChoice == 1) {
        level = new EasyLevel();
    }
    else if (levelChoice == 2) {
        level = new IntermediateLevel();
    }
    else if (levelChoice == 3) {
        level = new AdvancedLevel();
    }
    else {
        std::cerr << "Invalid level choice!" << std::endl;
        return 1;
    }

    Game game(*level, playerName);
    game.play();

    delete level; // Clean up dynamically allocated memory
    system("pause");
    return 0;
}
