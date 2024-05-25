import xml.etree.ElementTree as ET
import numpy as np

def parse_camera_params(xml_file):
    tree = ET.parse(xml_file)
    root = tree.getroot()
    
    camera = root.find('camera')
    
    position = camera.find('position')
    pos = np.array([float(position.get('x')), float(position.get('y')), float(position.get('z'))])
    
    look_at = camera.find('lookAt')
    look = np.array([float(look_at.get('x')), float(look_at.get('y')), float(look_at.get('z'))])
    
    up = camera.find('up')
    up_vector = np.array([float(up.get('x')), float(up.get('y')), float(up.get('z'))])
    
    projection = camera.find('projection')
    fov = float(projection.get('fov'))
    near = float(projection.get('near'))
    far = float(projection.get('far'))
    
    return pos, look, up_vector, fov, near, far

def normalize_plane(plane):
    norm = np.linalg.norm(plane[:3])
    return plane / norm

def extract_frustum_planes(view_proj_matrix):
    planes = []
    planes.append(view_proj_matrix[3] + view_proj_matrix[0])  # Left
    planes.append(view_proj_matrix[3] - view_proj_matrix[0])  # Right
    planes.append(view_proj_matrix[3] + view_proj_matrix[1])  # Bottom
    planes.append(view_proj_matrix[3] - view_proj_matrix[1])  # Top
    planes.append(view_proj_matrix[3] + view_proj_matrix[2])  # Near
    planes.append(view_proj_matrix[3] - view_proj_matrix[2])  # Far
    
    return [normalize_plane(plane) for plane in planes]

def compute_view_matrix(pos, look, up):
    forward = look - pos
    forward /= np.linalg.norm(forward)
    
    right = np.cross(up, forward)
    right /= np.linalg.norm(right)
    
    up = np.cross(forward, right)
    
    view = np.eye(4)
    view[0, :3] = right
    view[1, :3] = up
    view[2, :3] = -forward
    view[:3, 3] = -np.dot(view[:3, :3], pos)
    
    return view

def compute_projection_matrix(fov, aspect_ratio, near, far):
    f = 1.0 / np.tan(np.radians(fov) / 2.0)
    
    proj = np.zeros((4, 4))
    proj[0, 0] = f / aspect_ratio
    proj[1, 1] = f
    proj[2, 2] = (far + near) / (near - far)
    proj[2, 3] = (2 * far * near) / (near - far)
    proj[3, 2] = -1.0
    
    return proj

def calculate_frustum_planes(xml_file):
    pos, look, up, fov, near, far = parse_camera_params(xml_file)
    
    aspect_ratio = 1.0  # Assuming square aspect ratio based on window dimensions
    
    view_matrix = compute_view_matrix(pos, look, up)
    projection_matrix = compute_projection_matrix(fov, aspect_ratio, near, far)
    
    view_proj_matrix = np.dot(projection_matrix, view_matrix)
    
    frustum_planes = extract_frustum_planes(view_proj_matrix)
    
    return frustum_planes

def main():
    xml_file = 'scenes/test/test_4_6.xml'  # Replace with the path to your XML file
    frustum_planes = calculate_frustum_planes(xml_file)
    
    for i, plane in enumerate(frustum_planes):
        normal = plane[:3]
        distance = plane[3]
        print(f"Plane {i}: Normal = {normal}, Distance = {distance}")

if __name__ == "__main__":
    main()
