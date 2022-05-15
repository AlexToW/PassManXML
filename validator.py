from lxml import etree
import sys


def validate(path_xsd = "schema.xsd", path_xml = "data.xml"):
    try:
        schema_root = etree.parse(path_xsd)
        schema = etree.XMLSchema(schema_root)
        xml = etree.parse(path_xml)
    except etree.ParseError as err:
        print(err)
        return False
    valid = schema.validate(xml)
    return valid


def main():
    result1 = 0
    result2 = 0
    if(len(sys.argv) == 5):
        # scheme_data data.xml scheme_auth auth.xml
        path_data_xsd = sys.argv[1]
        path_data_xml = sys.argv[2]
        path_auth_xsd = sys.argv[3]
        path_auth_xml = sys.argv[4]
        result1 = validate(path_xsd=path_data_xsd, path_xml=path_data_xml)
        result2 = validate(path_xsd=path_auth_xsd, path_xml=path_auth_xml)
    
    validate_path = "validate.txt"
    with open(validate_path, "w") as file:
        file.write(f"{int(result1 and result2)}")


main()
