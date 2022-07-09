'''
    Validation of the data.xml and authorization.xml files according 
    to the appropriate schemes for both empty files (for example, 
    the user has registered but has not created any password) and data files.
'''

from lxml import etree


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
    scheme_data = "scheme_data.xsd"
    scheme_data_2 = "scheme_data_2.xsd"
    scheme_auth = "scheme_auth.xsd"
    scheme_auth_2 = "scheme_auth_2.xsd"
    path_data_xml = "data.xml"
    path_auth_xml = "authorisation.xml"
    result1 = validate(path_xsd=scheme_data, path_xml=path_data_xml) or validate(path_xsd=scheme_data_2, path_xml=path_data_xml)
    result2 = validate(path_xsd=scheme_auth, path_xml=path_auth_xml) or validate(path_xsd=scheme_auth_2, path_xml=path_auth_xml)
    
    validate_path = "validate.txt"
    with open(validate_path, "w") as file:
        file.write(f"{int(result1 and result2)}")


main()
