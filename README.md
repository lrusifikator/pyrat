This is a program for piracy on YouTube
<p>
This programm just search the most liked video for today on some topic and upload it on your channel


Requirements:

google api and the progress bar
<p>
sudo pip install --upgrade google-api-python-client progressbar2
<p>
  
youtube-dl
sudo wget https://yt-dl.org/downloads/latest/youtube-dl -O /usr/local/bin/youtube-dl
<p>
sudo chmod a+rx /usr/local/bin/youtube-dl

youtube upload script
git clone https://github.com/tokland/youtube-upload.git
<p>
cd youtube-upload
<p>
sudo python setup.py install

Also you need a google OAuth 2.0 key for your channel, and enable google youtube-api libraries.

Usage : 
<p>
pyrat db                            - open the database file with nano\
<p>
pyrat database						- same like "pyrat db"
<p>
pyrat rm <topic> 					- delete topic
<p>
pyrat rm backup                     - delete all backup links
<p>
pyrat rm backup <topic>             - delete backup links from topic
<p>
pyrat add topic|search word|categoty   - add an entry. One entry is one channel. For every channel you need a single key, topic name, search word and catgory
<p>
pyrat add key <path/to/key> <topic> - add a Auth2 json key
<p>
pyrat show 							- show all entries						
<p>
pyrat show <topic>					- show entry for topic
<p>
pyrat show -cat                     - show all available categories
<p>  
pyrat show --categories             - same like "pyrat show -cat"
<p>
pyrat run <topic>                   - run pyrat for a topic
