# decqueueCardGame
This is the first project in my CS 315 (Algorithms) course, lectured and assigned by Dr. Raphael Finkel.

"Each of n players starts with c cards arranged in a pile. These cards have value 1 ... c, with the 1 card on the top. 
The weight of the pile is the sum of d*v, where d is the depth of each card (starting at 1) and v is its value. 
So the starting weight of each pile is 1*1 + 2*2 + ... + c*c = c(c+1)(2c+1)/6. Higher-weight piles are worse; the goal is to have 0 weight, that is, no cards at all. 
At each turn, someone tosses an n-sided die, which indicates which player p will have the advantage on this turn. 
Player p tosses a 2-sided die, indicating whether to discard a card from the top (if the die shows 1) or the bottom of its pile (if the die shows 2), and an n-sided die, indicating which player accepts the discarded card. 
It is possible for p to get its own card back. The recipient puts the accepted card at the top of its pile.
The winner is the first player to have an empty pile. If after t turns, no player has won, then the player whose pile has the smallest weight wins. If there is a tie, the lowest-numbered player with the smallest weight wins." (Finkel, Programming Assignment: Deck of Dequeues).
