
import json

from django.shortcuts import render, redirect

# Create your views here.
from .models import Bee, Result
from .forms import AddBeeForm

from queen_app.tasks import send_request

def index(request):
	template = 'queen/index.html'
	bees = Bee.objects.all().order_by('name')

	context = {
		'bees': bees
	}

	return render(request, template, context)

def add_bee(request):
	# TODO add auth
	template = 'queen/add_bee.html'

	form = AddBeeForm(request.POST or None)

	if form.is_valid():
		form.save(commit=True)
		return redirect('/')
	else:
		form = AddBeeForm()

	context = {
		'form': form
	}

	return render(request, template, context)

def parse_result(j):
	s = json.loads(j)
	out = ''
	for scan in s['scans']:
		t = scan['type']
		out += '<h2 class="subheading">'+ t + '</h2><br>\n'
		for file in scan['files']:
			out += file['name'] + ' = ' + file['J'] + '<br>\n'
	return out

def view_bee(request, slug):
	template = 'queen/view_bee.html'

	try:
		bee = Bee.objects.get(slug=slug)
	except Bee.DoesNotExist:
		return redirect('/')

	if bee.status == 'Complete':
		result = Result.objects.get(bee=bee)
		body = parse_result(result.result)
	elif bee.status == 'Scanning':
		body = 'Still scanning'
	else:
		body = 'Needs scanned'

	context = {
		'bee': bee,
		'body': body
	}

	return render(request, template, context)

def scan_bee(request, slug):
	try:
		bee = Bee.objects.get(slug=slug)
	except Bee.DoesNotExist:
		return redirect('/')

	send_request.delay(bee.id)
	return redirect('queen_app:bee', slug=slug)

