import json
if __name__ == '__main__':
    try:
        with open('text.json', 'r') as file:
            data = json.loads(file.read())

        output = ','.join([*data[0]])
        for obj in data:
            output += f'\n{obj["Name"]},{obj["age"]},{obj["birthyear"]}'

        with open('output.csv', 'w') as file:
            file.write(output)
    except Exception as ex:
        print(f'Error: {str(ex)}')