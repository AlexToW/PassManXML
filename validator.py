from lxml import etree
import sys


def validate(path_xsd = "schema.xsd", path_xml = "data.xml"):
    try:
        schema_root = etree.parse(path_xsd)
        schema = etree.XMLSchema(schema_root)
        xml = etree.parse(path_xml)
    except etree.ParseError as err:
        print(err)
        return 0
    valid = schema.validate(xml)
    return valid


def main():
    result = 0
    if(len(sys.argv) == 3):
        path_xsd = sys.argv[1]
        path_xml = sys.argv[2]
        result = validate(path_xsd=path_xsd, path_xml=path_xml)
    else:
        result = validate()
    
    validate_path = "validate.txt"
    with open(validate_path, "w") as file:
        file.write(f"{int(result)}")


main()
