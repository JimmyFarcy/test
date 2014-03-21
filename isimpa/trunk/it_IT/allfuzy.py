fich=open("internat.po","r")
fichout=open("internat_fuzzy.po","w")
def dofuzzy(inf,outf):
    fich=open(inf,"r")
    fichout=open(outf,"w")
    if not fichout:
        return False
    nextcformat=False
    for line in fich:
        if line.startswith("msgid"):
            if not nextcformat:
                fichout.write("#, fuzzy\n")
            else:
                fichout.write("#, fuzzy, c-format\n")
                nextcformat=False
        if line.startswith("#,"):
            if "c-format" in line:
                nextcformat=True
            line=""
        fichout.write(line)
    fich.close()
    fichout.close()
dofuzzy("internat.po","internat_fuzzy.po")
