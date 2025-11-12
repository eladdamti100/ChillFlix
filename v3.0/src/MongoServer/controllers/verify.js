const userService = require('../services/user');

async function verify(req, res, next) {
  // Check for Authorization header to get the token (user-id in this case)
  const authHeader = req.headers['authorization'];
  if (!authHeader) {
    return res.status(400).json({ error: 'Authorization header not provided' });
  }

  try {
    const userId = authHeader;

    if (!userId) {
      return res.status(400).json({ error: 'User ID not provided in the token' });
    }

    // Get the user from the database
    const user = await userService.getUserById(userId);
    if (!user) {
      return res.status(404).json({ error: 'User not found' });
    }

    req.user = user;
    next();

  } catch (error) {
    console.error('Error during verification:', error.message);
    res.status(500).json({ error: 'Failed to verify user' });
  }
}

module.exports = verify;
