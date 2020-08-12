import time
import os, sys, stat

class VariablesStructure:
    def __init__(self, n, pth, short_n, addr, dflt):
        self.path = pth
        self.name = n
        self.short_name = short_n
        self.address = addr
        self.default = dflt
    def get_path(self):
        return self.path
    def get_name(self):
        return self.name
    def get_short_name(self):
        return self.short_name
    def get_address(self):
        return self.address
    def get_default(self):
        return self.default

variables = []

def find_and_collect_parameters_descriptors(file_name):
    f = open(file, "r")

    #1. find the variables names
    variables_name = []
    for line in f:
        if line.find("SystemParameters::SPSParamterDescriptor") is not -1:
            variable_name_start = line.find("m_") + 2
            variable_name_stop = line.find(";")
            name = line[variable_name_start : variable_name_stop]
            variables_name.append(name)

    #2. find all paramters for the variables
    for var in variables_name:
        f.seek(0)
        path_template = "#define PARAMETER_SHORT_PATH__" + var
        short_name_template = "#define PARAMETER_SHORT_NAME__" + var
        short_addr_template = "#define PARAMETER_ADDRESS__" + var
        short_default_template = "#define PARAMETER_DEFAULT__" + var
        parsed_values_count = 0
        for line in f:
            if line.find(path_template) is not -1:
                start = line.find("\"") + 1
                stop = start + line[start:].find("\"")
                path = line[start : stop]
                parsed_values_count = parsed_values_count + 1
            if line.find(short_name_template) is not -1:
                start = line.find("\"") + 1
                stop = start + line[start:].find("\"")
                short_name = line[start : stop]
                parsed_values_count = parsed_values_count + 1
            if line.find(short_addr_template) is not -1:
                start = line.find("(") + 1
                stop = start + line[start:].find(")")
                address = line[start : stop]
                parsed_values_count = parsed_values_count + 1
            if line.find(short_default_template) is not -1:
                start = line.find("(") + 1
                stop = start + line[start:].find(")")
                default = line[start : stop]
                parsed_values_count = parsed_values_count + 1
        if parsed_values_count is not 4:
            return False
        variables.append(VariablesStructure(var, path, short_name, address, default))
    f.close()
    return True

def validate_parameters():
    for param_under_validation in variables:
        for var in variables:
            if param_under_validation is var:
                continue
            if param_under_validation.get_address() is var.get_address():
                return False
            if param_under_validation.get_short_name() is var.get_short_name():
                return False
            if param_under_validation.get_name() is var.get_name():
                return False
    return True

def create_parameters_file(json_file_name):
    f = open(json_file_name, "w")
    f.write("{\n    \"Parameters\": \n    [\n")
    for var in variables:
        f.write("       { \"name\" : \"" + var.get_name() + "\", " )
        f.write("\"path\": \"" + var.get_path() + "\", ")
        f.write("\"short_name\": \"" + var.get_short_name() + "\", ")
        f.write("\"address\": " + str(var.get_address()) + ", ")
        f.write("\"default\": " + str(var.get_default()) + " ")

        if(var is not variables[len(variables)-1]):
            f.write("},\n")
        else:
            f.write("}\n")
    f.write("    ]\n}\n")
    f.flush()
    f.close()

#Set the target directory
dest_directory = '../../'
script_directory = os.getcwd()
os.chdir(dest_directory)
script_directory2 = os.getcwd()
#Get header files list
files = os.listdir("./")
header_files = filter(lambda x: x.endswith('.h'), files)

for file in header_files:
    if find_and_collect_parameters_descriptors(file) is not True:
        raise SystemExit(1)

#Create json file with paramters tree
os.chdir(script_directory)
script_directory2 = os.getcwd()

if validate_parameters() is not True:
    raise SystemExit(255)
create_parameters_file("sps_paramters.json")