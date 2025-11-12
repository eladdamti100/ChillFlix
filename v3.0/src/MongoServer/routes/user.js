const express = require('express');
const router = express.Router();
const userController = require('../controllers/user');
const verify = require('../controllers/verify');

router.route('/')
  .post(userController.createUser);

router.route('/all')
  .get(verify, userController.getAllUsers);

router.route('/:id')
  .get(userController.getUserById)
  .patch(verify, userController.updateUserDetails)
  //.delete(verify, userController.deleteUser);

module.exports = router;