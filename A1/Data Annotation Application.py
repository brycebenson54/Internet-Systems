def decode(message_file):
  # Initialize an empty list to store the message words
  message_words = []

  # Read the content of the file
  with open(message_file, 'r') as file:
      lines = file.readlines()

      # Iterate over each line in the file
      for i, line in enumerate(lines):
          # Split each line into number and word
          num, word = line.split()
          # Convert the number to integer
          num = int(num)

          # Append the word to the message words list if its number matches the current line number
          if num == i + 1:
              message_words.append(word)

  # Join the message words into a single string and return
  return ' '.join(message_words)

# Test the function with a sample input file
                                                       
decoded_message = decode("C:\\Users\\nisel\\Downloads\\coding_qual_input.txt")
print(decoded_message)