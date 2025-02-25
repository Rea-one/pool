import subprocess


class paths:
    def __init__(self):
        self.p = {}
    
    def set(self, guide, path):
        self.p[guide] = path
        
    def read_dictionary(self, dictionary):
        self.p = dictionary
        
    def __getitem__(self, guide):
        message = ''
        idx = ''
        condition = True
        
        for elem in self.p[guide]:
            if elem == '\\':
                condition = not condition
                if condition:
                    message += self.p[idx]
                continue
            if condition:
                message += elem
            else:
                idx += elem
                
        if condition:
            return message
        
pt_b_dictionary = {
    'Qt6': '/home/vesita/Qt/6.8.2/gcc_64',
    'qt6cmd_tool': '\\Qt6\\/libexec'
}

pt_b = paths()
pt_b.read_dictionary(pt_b_dictionary)

class comands:
    def __init__(self):
        self.condition = None
        self.C = {}
    
    def set(self, guide, command):
        self.C[guide] = command
    
    def read_dictionary(self, dictionary):
        self.C = dictionary
    
    def run(self, guide=None):
        if guide is None:
            for key, value in self.C.items():
                subprocess.run(value, shell=True)
        elif isinstance(guide, list):
            for elem in guide:
                subprocess.run(self[elem], shell=True)
        else:
            subprocess.run(self[guide], shell=True)
    
    def __getitem__(self, guide):
        message = ''
        idx = ''
        condition = True
        
        for elem in self.C[guide]:
            if elem == '\\':
                condition = not condition
                if condition:
                    message += pt_b[idx]
                continue
            if condition:
                message += elem
            else:
                idx += elem
                
        if condition:
            return message

cmd_b = comands()

cmd_b_dictionary = {
    'uic': '\\qt6cmd_tool\\/uic mainwindow.ui -o ui_mainwindow.h'
}

cmd_b.read_dictionary(cmd_b_dictionary)


# class cmaker():
#     def __init__(self):
#         self.language = None
#         self.project_name = None
#         self.standards = None
#         self.pakage_paths = None
#         self.ex_tars = None
#         self.links = None
    
#     def __len__(self):
#         return 6
    
#     def __getitem__(self, index):
#         if index == 0:
#             return self.language
#         elif index == 1:
#             return self.project_name
#         elif index == 2:
#             return self.standards
#         elif index == 3:
#             return self.pakage_paths
#         elif index == 4:
#             return self.ex_tars
#         elif index == 5:
#             return self.links


if __name__ == '__main__':
    print(cmd_b['uic'])