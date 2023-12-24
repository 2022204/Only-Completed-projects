import pygame
import sys
import Trie_Class

# Initialize Pygame modules
pygame.init()

# Define constants
GRID_COL = 12
GRID_ROW = 7
CELL_SIZE = 30
WIDTH = GRID_COL * CELL_SIZE
HEIGHT = GRID_ROW * CELL_SIZE
CHECK_BUTTON_WIDTH = 100
CHECK_BUTTON_HEIGHT = 40
MARGIN = 10

# Define colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
GREEN = (0, 255, 0)

# Define the puzzle grid
puzzle = [['d', 'o', 'g', 'x', 'b', 'x', 'x', 'x', 'n', 'o', 'o', 'n'],
          ['r', 'h', 'e', 'l', 'l', 'o', 't', 'h', 'e', 'r', 'e', 'x'],
          ['o', 'k', 'c', 'i', 'u', 'q', 'b', 'r', 'o', 'w', 'n', 'm'],
          ['w', 'x', 'w', 'g', 'e', 'x', 'l', 'x', 'h', 'j', 'i', 'j'],
          ['o', 'o', 'z', 'o', 'k', 'v', 'u', 'x', 'd', 'r', 'o', 'w'],
          ['r', 'l', 'x', 'd', 'r', 'x', 'e', 'x', 't', 'x', 'j', 'a'],
          ['d', 'r', 'o', 'w', 'b', 'l', 'o', 'n', 'k', 'g', 'o', 'd']]

# Create the game window
screen = pygame.display.set_mode((WIDTH + CHECK_BUTTON_WIDTH + MARGIN, HEIGHT))
pygame.display.set_caption("Puzzle Grid in Pygame")

# Create a check button
check_button_rect = pygame.Rect(WIDTH + MARGIN, MARGIN, CHECK_BUTTON_WIDTH, CHECK_BUTTON_HEIGHT)
check_button_font = pygame.font.Font(None, 36)
check_button_text = check_button_font.render("Check", True, WHITE)
check_button_text_rect = check_button_text.get_rect(center=check_button_rect.center)

def draw_puzzle_grid(puzzle, selected_cells, correct_cells, incorrect_cells):
    for row in range(GRID_ROW):
        for col in range(GRID_COL):
            if (row, col) in correct_cells:
                color = GREEN
            elif (row, col) in incorrect_cells:
                color = RED
            elif (row, col) in selected_cells:
                color = WHITE
            else:
                color = BLACK

            pygame.draw.rect(screen, color, (col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE), 0)

            font = pygame.font.Font(None, 36)

            text = font.render(puzzle[row][col], True, BLACK if color == WHITE else WHITE)
            text_rect = text.get_rect(center=(col * CELL_SIZE + CELL_SIZE // 2, row * CELL_SIZE + CELL_SIZE // 2))
            screen.blit(text, text_rect)

def print_puzzle():
    for i in range(len(puzzle)):
        print()
        for j in range(len(puzzle[i])):
            print(" ", puzzle[i][j], end=" ")
        print()

def main():
    mytrie = Trie_Class.Trie()
    mytrie.solve(puzzle)

    selected_cells = []
    correct_cells = set()
    incorrect_cells = set()
    check_mode = False  # Variable to indicate whether we are in check mode

    # Main game loop
    running = True
    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False
            elif event.type == pygame.MOUSEBUTTONDOWN:
                if check_button_rect.collidepoint(event.pos):
                    # Clicked the check button, toggle check mode
                    check_mode = not check_mode
                    if check_mode:
                        # Check the word when entering check mode
                        word = ''.join(puzzle[row][col] for row, col in selected_cells)
                        if mytrie.search(word):
                            correct_cells.update(selected_cells)
                        else:
                            incorrect_cells.update(selected_cells)
                        # Clear selected cells when entering check mode
                        selected_cells.clear()
                elif not check_mode:
                    # Get the cell coordinates based on the mouse position
                    col = event.pos[0] // CELL_SIZE
                    row = event.pos[1] // CELL_SIZE

                    # Add the selected cell to the list
                    selected_cells.append((row, col))
            elif event.type == pygame.KEYDOWN and event.key == pygame.K_RETURN:
                # Pressed the Enter key, perform check
                if check_mode:
                    word = ''.join(puzzle[row][col] for row, col in selected_cells)
                    if mytrie.search(word):
                        correct_cells.update(selected_cells)
                    else:
                        incorrect_cells.update(selected_cells)
                    # Clear selected cells after check
                    selected_cells.clear()

        # Draw the puzzle grid
        screen.fill(BLACK)
        draw_puzzle_grid(puzzle, selected_cells, correct_cells, incorrect_cells)

        # Draw the check button
        pygame.draw.rect(screen, (50, 50, 50), check_button_rect)
        screen.blit(check_button_text, check_button_text_rect)

        # Update the display
        pygame.display.flip()

    pygame.quit()
    sys.exit()

if __name__ == "__main__":
    main()

"""
add valid box checker
add life
add time
add score card (life and time function)
add difficulty
make box look better
remove the double click on check button (optional)
"""