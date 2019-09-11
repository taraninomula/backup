import random 
comp_gen = random.randint(1,100)
count = 0
def get_guess():
	global count
	count = count+1
	guess = input("Enter any number from 1 to 100")
	return guess

guess = get_guess()

while guess != comp_gen:
	if guess > comp_gen:
		print "Go lower!"
		guess = get_guess()
	else:
		print "Go higher!"
		guess = get_guess()

print "You won! and the number of guesses you made:", count
