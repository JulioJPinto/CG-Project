
// Frustum createFrustumFromCamera(const Camera& cam, float aspect, float fovY,
//                                                                 float zNear,
//                                                                 float zFar)
// {
//     Frustum     frustum;
//     const float halfVSide = zFar * tanf(fovY * .5f);
//     const float halfHSide = halfVSide * aspect;
//     const glm::vec3 frontMultFar = zFar * cam.Front;

//     frustum.nearFace = { cam.Position + zNear * cam.Front, cam.Front };
//     frustum.farFace = { cam.Position + frontMultFar, -cam.Front };
//     frustum.rightFace = { cam.Position,
//                             glm::cross(frontMultFar - cam.Right * halfHSide,
//                             cam.Up) };
//     frustum.leftFace = { cam.Position,
//                             glm::cross(cam.Up,frontMultFar + cam.Right *
//                             halfHSide) };
//     frustum.topFace = { cam.Position,
//                             glm::cross(cam.Right, frontMultFar - cam.Up *
//                             halfVSide) };
//     frustum.bottomFace = { cam.Position,
//                             glm::cross(frontMultFar + cam.Up * halfVSide,
//                             cam.Right) };

//     return frustum;
// }