headerFile = open("RSGL.h", 'w+')

def addFile(filename):
    file = open(filename, 'r')

    for line in file:
        if ("deps/RGFW.h" in line):
            addFile("./include/deps/RGFW.h")
            addFile("./include/keys.h")
            continue

        if ("#ifdef" in line and "_IMPLEMENTATION" in line):
            break
        
        headerFile.write(line)
    
    file.close()


fileNames = ["./include/RSGL.h", "./include/rphys.h"]

for filename in fileNames:
    addFile(filename)

headerFile.close()