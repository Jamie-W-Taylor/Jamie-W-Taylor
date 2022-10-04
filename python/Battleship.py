from random import randint

# import random so ship will be in a random location

board = []

for x in range(5):
    board.append(["O"] * 5)  # creates the board with 5 rows and column


def print_board(board):
    for row in board:
        print(" ".join(row))


print("Let's play Battleship!")
print_board(board)  # displays the board for the user


def random_row(board):
    return randint(0, len(board) - 1)


def random_col(board):
    return randint(0, len(board[0]) - 1)


ship_row = random_row(board)
ship_col = random_col(board)
# sets ship on random Row and Column

for turn in range(11):  # allows for loop up to 11 times

    guess_row = int(input("Guess Row:"))
    guess_col = int(input("Guess Col:"))

    if guess_row == ship_row and guess_col == ship_col:
        print("Congratulations! You sunk my battleship!")
        break  # if you guess correct row and column output that you've won and end the program
    else:
        if turn == 10:
            print("Game Over")
            # if you take 10 turns end the game

        elif (guess_row < 0 or guess_row > 4) or (guess_col < 0 or guess_col > 4):
            print("Oops, that's not even in the ocean.")
        elif (board[guess_row][guess_col] == "X"):
            print("You guessed that one already.")
        else:
            print("You missed my battleship!")
            board[guess_row][guess_col] = "X"  # if guessed wrong set the choice as an X
        print("Turn:", turn + 1)
        print_board(board)  # add 1 to the turn count and print the board
