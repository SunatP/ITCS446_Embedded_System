var mongoose = require("mongoose");
mongoose.connect("mongodb://192.168.43.65:27017/myDB", {
  useUnifiedTopology: true,
  useNewUrlParser: true,
});

mongoose.connection.on("error", (err) => {
    console.log(err);
  });
  
  mongoose.connection.on("connected", (err, res) => {
    console.log("mongoose is connected");
  });