import matplotlib.pyplot as plt

def read_points_from_file(filename):
  """
  Reads points from a file in the original format (3 numbers per line)
  and returns a list of tuples representing the points.
  """

  points = []
  with open(filename, 'r') as file:
    for line in file:
      # Split the line using spaces as delimiters
      x, y, z = map(float, line.strip().split())
      points.append((x, y, z))
  return points

# Read points from the file (replace "points.txt" with your actual file name)
points = read_points_from_file("models/sphere.3d")

# Extract x, y, and z coordinates
x = [point[0] for point in points]
y = [point[1] for point in points]
z = [point[2] for point in points]

# Create the 3D plot
fig = plt.figure(figsize=(8, 6))
ax = fig.add_subplot(111, projection='3d')
ax.scatter(x, y, z, c='blue', marker='o')

# Set labels and title
ax.set_xlabel('X')
ax.set_ylabel('Y')
ax.set_zlabel('Z')
ax.set_title('3D Scatter Plot of Points')

# Rotate the plot for better viewing
ax.view_init(elev=15, azim=-60)

# Show the plot
plt.show()
