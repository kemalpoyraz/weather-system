#!/usr/bin/env python
import urllib2,json
from pprint import pprint

READ_API_KEY='XF4DUHJ7I1WPYOQ3'
CHANNEL_ID=247550

def main():

    conn = urllib2.urlopen("http://api.thingspeak.com/channels/%s/feeds.json?api_k$
                           % (CHANNEL_ID,READ_API_KEY))
    response = conn.read()
    print "http status code=%s" % (conn.getcode())
    data=json.loads(response)

    f = open('temperatureEncryptedResult.txt', 'w')

    feeds = data['feeds']
    for feed in feeds:
        f.write(feed['field3'] + '\n')

    f.close()

    f = open('pressureEncryptedResult.txt', 'w')

    for feed in feeds:
        f.write(feed['field4']);

    f.close();

    conn.close()

if __name__ == '__main__':
    main()
