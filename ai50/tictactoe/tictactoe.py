"""
Tic Tac Toe Player
"""

from copy import deepcopy
import math

X = "X"
O = "O"
EMPTY = None
BOARD_SIZE = 3


def initial_state():
    """
    Returns starting state of the board.
    """
    return [[EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY],
            [EMPTY, EMPTY, EMPTY]]


def player(board):
    """
    Returns player who has the next turn on a board.
    """
    X_count = 0
    O_count = 0
    EMPTY_count = 0

    for row in board:
        X_count += row.count(X)
        O_count += row.count(O)
        EMPTY_count += row.count(EMPTY)

    if X_count > O_count:
        return O
    else:
        return X


def actions(board):
    """
    Returns set of all possible actions (i, j) available on the board.
    """
    moves = set()

    for i in range(BOARD_SIZE):
        for j in range(BOARD_SIZE):
            if board[i][j] == EMPTY:
                moves.add((i, j))

    return moves


def result(board, action):
    """
    Returns the board that results from making move (i, j) on the board.
    """

    i = action[0]
    j = action[1]

    # Check move is valid:
    if i not in [0, 1, 2] or j not in [0, 1, 2]:
        raise Exception('invalid move')
    elif board[i][j] != EMPTY:
        raise Exception('invalid move')

    board_copy = deepcopy(board)
    board_copy[i][j] = player(board)

    return board_copy


def winner(board):
    """
    Returns the winner of the game, if there is one.
    """
    X_pattern = 'X' * BOARD_SIZE
    O_pattern = 'O' * BOARD_SIZE

    for row in board:
        if row.count(X) == BOARD_SIZE:
            return X

        if row.count(O) == BOARD_SIZE:
            return O

    for j in range(BOARD_SIZE):
        column = ''
        for i in range(BOARD_SIZE):
            column += str(board[i][j])

        if column == X_pattern:
            return X

        if column == O_pattern:
            return O

    diagL = ''
    diagR = ''
    j = 2

    for i in range(BOARD_SIZE):
        diagL += str(board[i][i])
        diagR += str(board[i][j])
        j -= 1

    if diagL == X_pattern or diagR == X_pattern:
        return X
    elif diagL == O_pattern or diagR == O_pattern:
        return O

    return None


def terminal(board):
    """
    Returns True if game is over, False otherwise.
    """

    if winner(board) or not actions(board):
        return True
    else:
        return False


def utility(board):
    """
    Returns 1 if X has won the game, -1 if O has won, 0 otherwise.
    """

    if winner(board) == 'X':
        return 1
    elif winner(board) == 'O':
        return -1
    else:
        return 0


def minimax(board):
    """
    Returns the optimal action for the current player on the board.
    """

    if terminal(board):
        return None

    current_player = player(board)
    best_value = float('-inf') if current_player == 'X' else float('inf')
    best_action = None

    for action in actions(board):
        new_board = result(board, action)
        value = minimax_value(new_board, current_player == 'X')

        if current_player == 'X':
            if value > best_value:
                best_value = value
                best_action = action
        else:
            if value < best_value:
                best_value = value
                best_action = action

    return best_action


def minimax_value(board, maximizing_player):

    if terminal(board):
        return utility(board)

    if maximizing_player:
        value = float('-inf')
        for action in actions(board):
            value = max(value, minimax_value(result(board, action), False))
        return value
    else:
        value = float('inf')
        for action in actions(board):
            value = min(value, minimax_value(result(board, action), True))
        return value
