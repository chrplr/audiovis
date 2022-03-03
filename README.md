# audiovis: a general audio visual stimulus presentation script using expyriment

christophe@pallier.org

Github repository: <https://github.com/chrplr/audiovis>


`audiovis.py` plays audio or visual stimuli (images or text) according to a pre-specified timing schedule. 

The stimuli are listed in text files having one row per stimulus and 3 (comma separated) columns:


* col1 specifies the onset times in milliseconds.
* col2 specifies the type of stimulus: currently the program recognizes 'sound', 'picture', 'text' or 'rsvp'
* the content of col3 depends on the stimulus type:
    - a filename for 'sound' or 'picture' stimuli
    - a string of characters for 'text' or 'rsvp'

Several csv filenames can be passed as arguments on the command line (they will simply be merged)

audiovis requires the [expyriment module](https://expyriment.org) 

Try:

    python audiovis.py  sounds/list1.csv  pictures/list1.csv  speech/list1.csv 

Press 't' to start the stimulation (during the stimulation, you can always press `Esc` to interrupt the script).

Then try:

    python audiovis.py  rsvp/list1.csv sounds/list1.csv


To get the full list of options: 

    python audiovis.py -h

For example, it is possible to display a picture, e.g. containing instructions, using the --splash option. The computer will display this picture and then wait for the participant to press the spacebar to start the experiment.

    python audiovis.py --splash instructions.jpg --text-font TITUSCBZ.TTF --background-color 127 127 127 -- rsvp/list1.csv sounds/list1.csv


Christophe Pallier




