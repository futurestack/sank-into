"""converts xxx yyy to lua xdata = { xxx } ydata = { yyy }"""

def myReadFile( path):
    """reads a file to a list"""
    f = open(path,'r')
    result = f.readlines()
    f.close
    return result


import sys
print sys.argv # returns: ['param.py']

filename = sys.argv[1]
print filename

lines = myReadFile(filename)

xdata = [];
ydata = [];

outfilename = filename + ".lua"

outfile = open(outfilename,'w')
for line in lines:
    result = line.rstrip('\n')
    splitresult = result.split(' ')
    x = splitresult[0]
    y = splitresult[1]
    xdata.append(x)
    ydata.append(y)
    #print "x=%s/y=%s" % (x,y)




xstring = "xdata = {"
for i in xdata:
    xstring += i
    xstring += ","
xstring = xstring[:-1]
xstring +="}\n"

ystring = "ydata = {"
for i in ydata:
    ystring += i
    ystring += ","
ystring = ystring[:-1]
ystring +="}\n"


print xstring
print ystring

outfile.write(xstring)
outfile.write(ystring)