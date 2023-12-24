class Trie:
    class Node:
        def __init__(self):
            self.end = False
            self.next = [None] * 26

    def __init__(self):
        self.trie = self.Node()

    def insert(self, word):
        word = word.lower()
        itr = self.trie
        for char in word:
            if itr.next[ord(char) - ord('a')] is None:
                itr.next[ord(char) - ord('a')] = self.Node()
            itr = itr.next[ord(char) - ord('a')]
        itr.end = True

    def index_checker(self, index_r, index_c, ROW, COLUMN):
        if index_r < 0 or index_c < 0 or index_r >= ROW or index_c >= COLUMN:
            return False
        return True

    def solve_board(self, direction_x, direction_y, row, col, board):
        itr = self.trie
        word = ""
        index_r = row
        index_c = col
        while True:
            if itr.end:
                index_r -= direction_x
                index_c -= direction_y
                result_str = f'{word},"{row},{col}","{index_r},{index_c}"\n'
                return result_str

            if itr.next is None:
                return None
            else:
                word += board[index_r][index_c]
                next_node = itr.next[ord(board[index_r][index_c]) - ord('a')]
                if next_node is None:
                    return None
                itr = next_node
                index_r += direction_x
                index_c += direction_y
                if not self.index_checker(index_r, index_c, len(board), len(board[0])):
                    if itr is not None and itr.end:
                        result_str = f'{word},"{row},{col}","{index_r},{index_c}"\n'
                        return result_str
                    return None

    def solve(self, board):
        directions = [[0, -1], [-1, -1], [-1, 0], [-1, 1], [0, 1], [1, 1], [1, 0], [1, -1]]
        txt_file = "wordlist.txt"

        self.insert_file(txt_file)
        with open("solution.csv", 'w') as file:
            for i in range(len(board)):
                for j in range(len(board[i])):
                    for k in directions:
                        word = self.solve_board(k[0], k[1], i, j, board)
                        if word is not None:
                            file.write(word)

    def insert_file(self, file):
        with open(file, 'r') as f:
            for line in f:
                self.insert(line.strip())
    def search(self, word):
        word = word.lower()
        itr = self.trie
        for char in word:
            if itr.next[ord(char) - ord('a')] is None:
                return False
            itr = itr.next[ord(char) - ord('a')]
        return itr.end
