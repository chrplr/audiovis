# audiovis
general audio visual stimulus presentation with expyriment


audiovis.py plays audio or visual stimuli listed in csv files passed as command line arguments (several csv files can be listed: they will simply be merged)


Each csv file must contain 3 columns:

- col1 contains onset times in milliseconds, from the start of the experiment
- col2 contains a label for the stimulus type: currently the program recognizes 'sound', 'picture', 'text' or 'rsvp'
- the content of col3 depends on the stimulus type. It must be a filename in the case of 'sound' or 'picture', or a string to be displayed in case of 'text' or 'rsvp'

Try:

python audiovis.py  sounds/list1.csv  pictures/list1.csv  speech/list1.csv 

and

python audiovis.py  rsvp/list1.csv sounds/list1.csv


and 

python audiovis.py -h   for help



it is possible to display a picture (for example containing instructions), using the --splash option:

python audiovis.py --splash instructions.jpg --text-font TITUSCBZ.TTF --background-color 127 127 127 -- rsvp/list1.csv sounds/list1.csv

or

python audiovis.py --splash instructions.jpg rsvp/list1.csv sounds/list1.csv

and change the font, or the background color (not working well still)






