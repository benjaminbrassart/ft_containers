import re

class PairPrettyPrinter(object):
    def __init__(self, value):
        self.value = value

    def to_string(self):
        return self.value["first"]

    def display_hint(self):
        return "string"

def pair_lookup_function(val):
    tag = val.type.tag

    print(tag)

    if tag is None:
        return None

    regex = re.compile("^ft::pair<")

    if regex.match(tag):
        return PairPrettyPrinter(val)

    return None

gdb.pretty_printers.append(pair_lookup_function)
