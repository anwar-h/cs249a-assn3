
import argparse, inspect, sys, os, subprocess

anwar_default_path = "~/cs249a/assn2/"
michelle_default_path = "~/cs249a/hw2/"

def main():
	(anwar, michelle) = getCommandLineArgs()
	print anwar, michelle
	if not anwar and not michelle:
		exit(0)
	
	# Remember where we are now
	wkdir = getCurrentDirectory()
	command = "scp -r . %s@corn.stanford.edu:%s"
	if anwar:
		user = anwar
		path = anwar_default_path
		command = command % (user, path)
		subprocess.call(command, shell=True)
	if michelle:
		user = michelle
		path = michelle_default_path
		command = command % (user, path)
		subprocess.call(command, shell=True)
	
		
# Return the directory this process is currently in.
def getCurrentDirectory():
	return os.path.realpath(os.path.abspath(os.path.split(inspect.getfile( inspect.currentframe() ))[0]))
	
def getCommandLineArgs():
	parser = argparse.ArgumentParser(description='run scp on command line.')
	parser.add_argument('-a', metavar='Anwar SUNet ID', default=None)
	parser.add_argument('-m', metavar='Michelle SUNet ID', default=None)
	args = parser.parse_args()
	print "Example python scp.py -a ahahn -m mgumport"
	return (args.a, args.m)
	
if __name__ == "__main__":
	main()

