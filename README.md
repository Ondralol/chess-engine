## "Simple" Chess solver/bot

### Goal
- Create chess bot, that will never lose a game of chess (ideally the goal is to win the game)

### Problem analysis
- We have chess board of some size (in my case its 5x5 but can be changed to any "square" size) and we can place chess pieces (or custom versions of them) on the board however we want. Then I want to create chess bot that will find the best moves in order to win the game
- Considering the complexity of chess, for now I only created representation for the chess board and King and Rook pieces as well as simple Pawns without upgrade.

### Problem Solution
- The algorithm I used to find the best possible moves was MiniMax algorithm with AlphaBeta prunning. As evaluation of each branch I used the sum of values of each piece on the board for the active player. I also added extra evaluation points for checkmate/being checkmated and "punishment" for stalemate if there was a better move available
- Its important to mention that even with the prunning, I wasn't able to get past depths 7-10 due to computaional complexity even on 5x5 board with only a few pieces as there are billions of possible combinations. When experimenting I tried to lower the Rook range and that seemed to helped a lot with performace, which makes sense considering Rook has a large number of possible moves

### UI
- For better visualisation and also testing of all possible pieces moves I created interactive GUI for the chess board using SFML library, which can be also effectively used to play chess against the bot


