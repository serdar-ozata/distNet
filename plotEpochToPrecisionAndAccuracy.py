import matplotlib.pyplot as plt

def parse_line(line):
    """
    Parse the line to extract precision and accuracy.
    Handles both formats: '0.89, 0.93' and '0.89,0.93'.
    """
    # Split the line by ',' and strip spaces
    parts = [part.strip() for part in line.split(',')]
    precision = float(parts[0])
    accuracy = float(parts[1])
    return precision, accuracy

def plot_metrics(file_path, output_path):
    # Open the file and read the lines
    with open(file_path, 'r') as f:
        lines = f.readlines()

    # Strip the file and remove empty lines
    lines = [line.strip() for line in lines if line.strip()]

    # Prepare lists to store precision and accuracy values
    precisions = []
    accuracies = []

    # Parse each line to get precision and accuracy
    for line in lines:
        precision, accuracy = parse_line(line)
        precisions.append(precision)
        accuracies.append(accuracy)

    # Generate x values based on line numbers (1-indexed)
    # Ensure that x is an integer (epoch)
    x = list(range(1, len(lines) + 1))  # Epoch values (1, 2, 3, ...)

    # Create the plot
    plt.plot(x, precisions, label='Precision', color='blue', marker='o')
    plt.plot(x, accuracies, label='Accuracy', color='red', marker='x')

    # Add labels and title
    plt.xlabel('Epoch')
    plt.ylabel('Value')
    plt.title('Precision and Accuracy over Epochs')
    plt.legend()

    # Save the plot as an image file
    plt.savefig(output_path)
    print(f"Plot saved to {output_path}")

# Example usage
if __name__ == "__main__":
    # Replace with the path to your file and desired output image path
    file_path = 'metrics.txt'  # Input data file
    output_path = 'metrics_plot.png'  # Output image file
    plot_metrics(file_path, output_path)
