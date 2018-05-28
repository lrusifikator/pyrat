This is a program for piracy on YouTube

Requirements:

google api and the progress bar
sudo pip install --upgrade google-api-python-client progressbar2

youtube-dl
sudo wget https://yt-dl.org/downloads/latest/youtube-dl -O /usr/local/bin/youtube-dl
sudo chmod a+rx /usr/local/bin/youtube-dl

youtube upload script
git clone https://github.com/tokland/youtube-upload.git
cd youtube-upload
sudo python setup.py install

Also you need a google Auth2 json key for your chanall

Usage : 
pyrat db                            - open the database file with nano 
pyrat database						- same like "pyrat db"
pyrat rm <topic> 					- delete topic
pyrat rm backup                     - delete all backup links
pyrat rm backup <topic>             - delete backup links from topic
pyrat add topic|key word|categoty   - add an entry
pyrat add key <path/to/key> <topic> - add a Auth2 json key
pyrat show 							- show all entries						
pyrat show <topic>					- show entry for topic
pyrat show -cat                     - show all available categories
pyrat show --categories             - same like "pyrat show -cat"
pyrat run <topic>                   - run pyrat for a topic
