import csv
import math
import random

def process_and_split_files(input_file_x, input_file_y, train_file_x, test_file_x, train_file_y, test_file_y, train_split=0.8):
    # Read the files and remove empty lines
    with open(input_file_x, 'r') as infile_x, open(input_file_y, 'r') as infile_y:
        lines_x = [line.strip() for line in infile_x if line.strip()]
        lines_y = [line.strip() for line in infile_y if line.strip()]

    # Ensure both files have the same number of lines
    assert len(lines_x) == len(lines_y), "Input files must have the same number of lines."

    # Combine lines for synchronized shuffling
    combined = list(zip(lines_x, lines_y))
    random.shuffle(combined)

    # Split the combined data
    split_index = math.floor(train_split * len(combined))
    train_data = combined[:split_index]
    test_data = combined[split_index:]

    # Write the training data
    with open(train_file_x, 'w', newline='') as train_out_x, open(train_file_y, 'w', newline='') as train_out_y:
        train_writer_x = csv.writer(train_out_x)
        train_writer_y = csv.writer(train_out_y)
        for x, y in train_data:
            train_writer_x.writerow(x.split(','))
            train_writer_y.writerow(y.split(','))

    # Write the testing data
    with open(test_file_x, 'w', newline='') as test_out_x, open(test_file_y, 'w', newline='') as test_out_y:
        test_writer_x = csv.writer(test_out_x)
        test_writer_y = csv.writer(test_out_y)
        for x, y in test_data:
            test_writer_x.writerow(x.split(','))
            test_writer_y.writerow(y.split(','))


# Process files and split into train and test
process_and_split_files(
    "data/airline_passenger_satisfaction_x.csv",
    "data/airline_passenger_satisfaction_y.csv",
    "splitData/airline_passenger_satisfaction_x_train.csv",
    "splitData/airline_passenger_satisfaction_x_test.csv",
    "splitData/airline_passenger_satisfaction_y_train.csv",
    "splitData/airline_passenger_satisfaction_y_test.csv",
    train_split=0.8
)
