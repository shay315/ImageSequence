import pyImageSequence
seq = pyImageSequence.ImageElement(path="/mock/path/file.1003.exr")
other = pyImageSequence.ImageElement(path="/mock/path/file.1008.exr")

assert seq == other

assert seq.basename() == "file.%04d.exr"
assert seq.dirname() == "/mock/path"
assert seq.frames == [1003]


# Check property
seq.frames = list(range(1,4))
assert seq.frames == [1, 2, 3]



def testFunc():
        for imageSeq in pyImageSequence.scandir("/home/max-wi/dev/rnd/textures"):
            pass


import cProfile
cProfile.run("testFunc()")
