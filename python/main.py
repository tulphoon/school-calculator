expression = input('>>> ')
expression = expression.replace('(', ' ( ').replace(')', ' ) ').split()

operators = '*/+-'
stack = []
output = []

for token in expression:
    if token.isdigit():
        output.append(token)
    if token in operators:
        try:
            while operators.index(stack[-1]) < operators.index(token):
                output.append(stack.pop())
        except Exception as IndexError:
            pass
        stack.append(token)
    if token == '(':
        stack.append(token)
    if token == ')':
        if len(stack) > 0:
            while stack[-1] != '(':
                output.append(stack.pop())
            stack.pop()
    """
    print('token: ' + str(token))
    print('output: ' + str(output))
    print('stack: ' + str(stack))
    print('stack size: ' + str(len(stack)))
    """

while len(stack) > 0:
    output.append(stack.pop())

print(' '.join(output))
