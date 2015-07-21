import time
import urllib2
import threading
import pdb

class FetchUrls(threading.Thread):
        """
            Thread Checking URLs
        """
        def __init__(self, urls, output, lock):
            """
                Constructor
                @param urls list of urls to check
                @param ouytput file to write urls output
            """
            threading.Thread.__init__(self)
            self.urls = urls
            self.output = output
            self.lock = lock

        def run(self):
            """
            Thread run method Check URLs one by one
            """
            while self.urls:
                url = self.urls.pop()
                req = urllib2.Request(url)
                try:
                    d = urllib2.urlopen(req)
                except urllib2.URLError, e:
                    print 'URL %s failed: %s' % (url, e.reason)
                self.lock.acquire()
                print 'Lock Acquired by %s' % self.name
                self.output.write(d.read())
                print 'Write done by %s' % self.name
                print 'Lock released by %s' % self.name
                self.lock.release()
                print 'URL %s fetched by %s' % (url, self.name)

def main():

    urls1 = ['http://www.google.com', 'http://www.facebook.com']
    urls2 = ['http://www.yahoo.com', 'http://www.youtube.com']
    lock = threading.Lock()
    f = open('output.txt', 'w+')
    t1 = FetchUrls(urls1, f, lock)
    t2 = FetchUrls(urls2, f, lock)
    t1.start()
    t2.start()
    t1.join()
    t2.join()
    f.close()


if __name__=='__main__':
    #print 'I am here'
    #pdb.set_trace()
    main()
