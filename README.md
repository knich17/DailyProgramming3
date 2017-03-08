# Day 3 - Fallout Hacking Game
[Found at /r/dailyprogrammer](https://www.reddit.com/r/dailyprogrammer/comments/3qjnil/20151028_challenge_238_intermediate_fallout/)

## Problem Description
The popular video games Fallout 3 and Fallout: New Vegas have a computer "hacking" minigame where the player must correctly guess the correct password from a list of same-length words. Your challenge is to implement this game yourself.

## Solution
Uses a game loop to give the user the option of continuing to play.

Used some small math's formulas to calculate the number of words to use and word lengths as shown below.

'''C
//1=(5,6), 2=(7,8), 3=(9,10), 4=(11,12), 5=(13,14,15)
numWords = 5+2*(difficulty-1)+(rand()%2)+(floor(difficulty/5)*(rand()%2));
//1=(4,5), 2=(6,7), 3=(8,9), 4=(10,11), 5=(12,13,14,15)
wordLength= 4+2*(difficulty-1)+(rand()%2)+(floor(difficulty/5)*(rand()%4));
''''

Words were picked from the list by checking if they are the correct length, not already in the list of words to be used, as well as a random chance needing to be met (I used a 1 in 20000 chance).

Lastly, a magic word was picked randomly, guesses were collected and compared to the magic word and the game is won/lost based off if the user guessed correctly or ran out of guesses. Lastly the user is given the option to play again.

## Notes
Not too much learned from this exercise apart from a refresher on some C string annoyances which are never fun. As well as using maths instead of logic statements to determine the number and length of words to be used.