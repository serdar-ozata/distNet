import matplotlib.pyplot as plt

def parse_line(line):
    """
    Parse the line to extract number of nodes and average computation time.
    """
    # Split the line by ',' and strip spaces
    parts = [part.strip() for part in line.split(',')]
    nodes = int(parts[0])  # Number of nodes (int)
    avg_computation_time = float(parts[1])  # Average computation time (float)
    return nodes, avg_computation_time

def plot_metrics(file_path, output_path):
    # Open the file and read the lines
    with open(file_path, 'r') as f:
        lines = f.readlines()

    # Strip the file and remove empty lines
    lines = [line.strip() for line in lines if line.strip()]

    # Prepare lists to store nodes and average computation times
    nodes = []
    computation_times = []

    # Parse each line to get nodes and average computation time
    for line in lines:
        node, comp_time = parse_line(line)
        nodes.append(node)
        computation_times.append(comp_time)

    # Create the plot
    plt.plot(nodes, computation_times, label='Avg Computation Time per Epoch', color='green', marker='o')

    # Add labels and title
    plt.xlabel('Number of Nodes')
    plt.ylabel('Average Computation Time (in seconds)')
    plt.title('Computation Time per Epoch vs Number of Nodes')
    plt.legend()

    # Save the plot as an image file
    plt.savefig(output_path)
    print(f"Plot saved to {output_path}")

# Example usage
if __name__ == "__main__":
    # Replace with the path to your file and desired output image path
    file_path = 'nodes_computation_time.txt'  # Input data file
    output_path = 'nodes_computation_time_plot.png'  # Output image file
    plot_metrics(file_path, output_path)
