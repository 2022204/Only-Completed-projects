import pygame
import sys
import Trie_Class
import time
import csv
from datetime import datetime  
# Initialize Pygame modules
pygame.init()



# Define the puzzle grid
puzzle = [['d', 'o', 'g', 'x', 'b', 'x', 'x', 'x', 'n', 'o', 'o', 'n'],
          ['r', 'h', 'e', 'l', 'l', 'o', 't', 'h', 'e', 'r', 'e', 'x'],
          ['o', 'k', 'c', 'i', 'u', 'q', 'b', 'r', 'o', 'w', 'n', 'm'],
          ['w', 'x', 'w', 'g', 'e', 'x', 'l', 'x', 'h', 'j', 'i', 'j'],
          ['o', 'o', 'z', 'o', 'k', 'v', 'u', 'x', 'd', 'r', 'o', 'w'],
          ['r', 'l', 'x', 'd', 'r', 'x', 'e', 'x', 't', 'x', 'j', 'a'],
          ['d', 'r', 'o', 'w', 'b', 'l', 'o', 'n', 'k', 'g', 'o', 'd']]


# Define constants
GRID_COL = 12
GRID_ROW = 7
CELL_SIZE = 40
WIDTH = (GRID_COL * CELL_SIZE) + 5
HEIGHT = (GRID_ROW * CELL_SIZE) + 5
CHECK_BUTTON_WIDTH = 100
CHECK_BUTTON_HEIGHT = 40
MARGIN = 10

# Define colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)
GREEN = (0, 255, 0)


def save_score_to_csv(username, score):
    csv_file = 'scores.csv'

    timestamp = datetime.now().strftime("%Y-%m-%d %H:%M:%S")

    # Create or append to the CSV file
    with open(csv_file, mode='a', newline='') as file:
        writer = csv.writer(file)

        # Check if the file is empty (write headers if needed)
        if file.tell() == 0:
            writer.writerow(['Username','Score','Timestamp'])

        # Write the username, score, and timestamp to the CSV file
        writer.writerow([username, score,timestamp])


def get_user_name():
    screen = pygame.display.set_mode((400, 200))
    pygame.display.set_caption("Puzzle Grid in Pygame")

    font = pygame.font.Font(None, 36)
    input_box = pygame.Rect(50, 100, 300, 50)
    color_inactive = pygame.Color('lightskyblue3')
    color_active = pygame.Color('dodgerblue2')
    color = color_inactive
    user_name = ""
    active = True
    text = font.render(user_name, True, color)
    clock = pygame.time.Clock()

    enter_user_text = font.render("Enter Your Name", True, pygame.Color('white'))
    enter_user_rect = enter_user_text.get_rect(center=(200, input_box.y - 30))  # Centered alignment

    press_enter_text = font.render("Press Enter to continue", True, pygame.Color('white'))
    press_enter_rect = press_enter_text.get_rect(center=(200, input_box.y + input_box.h + 30))  # Centered alignment

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()
            if event.type == pygame.MOUSEBUTTONDOWN:
                if input_box.collidepoint(event.pos):
                    active = True
                else:
                    active = False
                color = color_active if active else color_inactive
            if event.type == pygame.KEYDOWN:
                if active:
                    if event.key == pygame.K_RETURN and user_name:
                        return user_name
                    elif event.key == pygame.K_BACKSPACE:
                        user_name = user_name[:-1]
                    else:
                        user_name += event.unicode
                    text = font.render(user_name, True, color)

        screen.fill((30, 30, 30))
        pygame.draw.rect(screen, color, input_box, 2)
        width = max(300, text.get_width() + 10)
        input_box.w = width
        screen.blit(text, (input_box.x + 5, input_box.y + 5))
        screen.blit(enter_user_text, enter_user_rect.topleft)
        screen.blit(press_enter_text, press_enter_rect.topleft)
        pygame.display.flip()
        clock.tick(30)



username=get_user_name()

# Create the game window
screen = pygame.display.set_mode((WIDTH + CHECK_BUTTON_WIDTH + MARGIN, HEIGHT))
pygame.display.set_caption("Puzzle Grid in Pygame")

# Create a check button
check_button_rect = pygame.Rect(WIDTH + MARGIN, MARGIN, CHECK_BUTTON_WIDTH, CHECK_BUTTON_HEIGHT)
check_button_font = pygame.font.Font(None, 36)
check_button_text = check_button_font.render("Check", True, WHITE)
check_button_text_rect = check_button_text.get_rect(center=check_button_rect.center)

# Set up the timer
start_time = time.time()
time_limit = 60  # 1 minute

# Set up the life system
max_lives = 5
current_lives = max_lives

def calculate_score(time_left, current_lives, multiplier):
    time_bonus = time_left * 0.2 * (multiplier + 1)
    lives_bonus = current_lives * multiplier
    return round((time_bonus + lives_bonus), 2)

def draw_puzzle_grid(puzzle, selected_cells, correct_cells, incorrect_cells, lives, time_left, display_score):
    for row in range(GRID_ROW):
        for col in range(GRID_COL):
            if display_score:
                # Clear the grid when displaying the score
                color = BLACK
            elif (row, col) in correct_cells:
                color = GREEN
            elif (row, col) in incorrect_cells:
                color = RED
            elif (row, col) in selected_cells:
                color = WHITE
            else:
                color = BLACK

            pygame.draw.rect(screen, color, (col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE), 0)

            font = pygame.font.Font(None, 36)

            if not display_score:
                text = font.render(puzzle[row][col], True, BLACK if color == WHITE else WHITE)
                text_rect = text.get_rect(center=(col * CELL_SIZE + CELL_SIZE // 2, row * CELL_SIZE + CELL_SIZE // 2))
                screen.blit(text, text_rect)

    if not display_score:
        # Display lives and time left
        font = pygame.font.Font(None, 24)

        # Convert elapsed_time to minutes and seconds
        minutes, seconds = divmod(int(time_left), 60)

        lives_text = font.render(f"Lives: {lives}", True, WHITE)
        lives_rect = lives_text.get_rect(midright=(WIDTH + CHECK_BUTTON_WIDTH + MARGIN - 5, HEIGHT // 2))
        screen.blit(lives_text, lives_rect)

        time_text = font.render(f"Time left: {minutes:02d}:{seconds:02d}", True, WHITE)
        time_rect = time_text.get_rect(midright=(WIDTH + CHECK_BUTTON_WIDTH + MARGIN - 5, HEIGHT // 2 + lives_text.get_height() + 5))
        screen.blit(time_text, time_rect)
    else:
        # Display the final score
        score = calculate_score(time_left, lives, len(correct_cells))
        font = pygame.font.Font(None, 48)
        score_text = font.render(f"{username}'s score: {score}", True, WHITE)
        save_score_to_csv(username, score)
        score_rect = score_text.get_rect(center=(WIDTH // 2, HEIGHT // 2))
        screen.blit(score_text, score_rect)






def validate_direction(selected_cells, new_cell):
    if not selected_cells:
        # No cells selected yet, allow any direction
        return True

    # Get the last selected cell
    last_cell = selected_cells[-1]

    # Define valid directions
    directions = [[0, -1], [-1, -1], [-1, 0], [-1, 1], [0, 1], [1, 1], [1, 0], [1, -1]]

    # Check if the new cell is in a valid direction from the last cell
    return [(new_cell[0] - last_cell[0]), (new_cell[1] - last_cell[1])] in directions

def main():
    mytrie = Trie_Class.Trie()
    mytrie.solve(puzzle)

    selected_cells = []
    correct_cells = set()
    incorrect_cells = set()
    check_mode = False  # Variable to indicate whether we are in check mode
    current_lives = 5
    running = True

    # Main game loop
    while running:
        elapsed_time = time.time() - start_time
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

                            # Deduct one life for each incorrect word
                            current_lives -= 1

                            # End the game if no lives left
                            if current_lives == 0:
                                running = False
                                  
                        # Clear selected cells when entering check mode
                        selected_cells.clear()
                elif not check_mode:
                    # Get the cell coordinates based on the mouse position
                    col = event.pos[0] // CELL_SIZE
                    row = event.pos[1] // CELL_SIZE

                    # Validate the direction of the new cell
                    if validate_direction(selected_cells, (row, col)):
                        # Add the selected cell to the list
                        selected_cells.append((row, col))
                    else:
                        # Invalid direction, clear selected cells
                        selected_cells.clear()
                        # Add the selected cell to the list
                        selected_cells.append((row, col))
                # Check if time has elapsed
            

        # Calculate time left
        elapsed_time = time.time() - start_time

        time_left = max(0, time_limit - elapsed_time)

        # Draw the puzzle grid
        screen.fill(BLACK)
        draw_puzzle_grid(puzzle, selected_cells, correct_cells, incorrect_cells, current_lives, time_left, False)

        # Draw the check button
        pygame.draw.rect(screen, (50, 50, 50), check_button_rect)
        screen.blit(check_button_text, check_button_text_rect)

        # Check if the game should end
        if time_left == 0 or current_lives == 0:
            # If the game ends, display the final score
            draw_puzzle_grid(puzzle, selected_cells, correct_cells, incorrect_cells, current_lives, time_left, True)
            pygame.display.flip()
            pygame.time.delay(3000)
            running = False
        # Update the display
        pygame.display.flip()
        

    # Display the final score
    pygame.quit()
    sys.exit()

        
if __name__ == "__main__":
    main()
"""
add valid box checker

remove the double click on check button (optional)
"""