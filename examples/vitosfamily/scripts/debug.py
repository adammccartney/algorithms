import gdb

class SimpleCommand(gdb.Command):

    def __init__(self):
        super(SimpleCommand, self).__init__("simple_command", gdb.COMMAND_DATA)

    def invoke(self, arg, from_tty):
        print("Hello from simple_command!")

SimpleCommand()
