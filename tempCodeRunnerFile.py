def draw_puzzle_grid(puzzle):
    for row in range(GRID_ROW):
        for col in range(GRID_COL):
            color = BLACK
            pygame.draw.rect(screen, color, (col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE), 0)

            font = pygame.font.Font(None, 36)
            text = font.render(puzzle[row][col], True, WHITE)
            text_rect = text.get_rect(center=(col * CELL_SIZE + CELL_SIZE // 2, row * CELL_SIZE + CELL_SIZE // 2))
            screen.blit(text, text_rect)