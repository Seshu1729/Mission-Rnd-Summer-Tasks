from __future__ import unicode_literals

from django.contrib.auth.models import User
from django.db import models

# Create your models here.
class project(models.Model):
    project_name = models.CharField(max_length=256)
    created_user = models.ForeignKey(User)

    def __str__(self):
        return self.project_name

class target(models.Model):
    project_name = models.ForeignKey(project,on_delete=models.CASCADE)
    target_name = models.CharField(max_length=256)
    description = models.TextField(max_length=100000)
    target_date = models.DateField()
    status = models.BooleanField(default=False)

    def __str__(self):
        return self.target_name